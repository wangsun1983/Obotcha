#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <memory.h>
#include <netinet/in.h>
#include <stddef.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include "ExecutorBuilder.hpp"
#include "Log.hpp"
#include "SocketMonitor.hpp"
#include "Inet6Address.hpp"
#include "NetEvent.hpp"

namespace obotcha {

_SocketMonitorTask::_SocketMonitorTask(int event, Socket s, ByteArray data) {
    this->event = event;
    this->sock = s;
    this->data = data;
}

_SocketMonitor::_SocketMonitor() : _SocketMonitor(1) {}

_SocketMonitor::_SocketMonitor(int threadnum) {
    mMutex = createMutex();
    mSocks = createHashMap<int, Socket>();
    mServerSocks = createHashMap<int, ServerSocket>();

    mPoll = createEPollFileObserver();
    mPoll->start();
    mThreadPublicTasks = createLinkedList<SocketMonitorTask>();
    mThreadLocalTasks = createArrayList<LinkedList<SocketMonitorTask>>();
    mCurrentSockets = new Socket[threadnum];
    mCondition = createCondition();

    mListenerMutex = createSpinLock();
    mListeners = createHashMap<int, SocketListener>();
    mThreadNum = threadnum;
    isStop = 1;

    for (int i = 0; i < threadnum; i++) {
        mThreadLocalTasks->add(createLinkedList<SocketMonitorTask>());
    }

    this->mExecutor =
        createExecutorBuilder()->setThreadNum(mThreadNum)->newThreadPool();
    for (int i = 0; i < mThreadNum; i++) {
        mExecutor->execute(
            [](int index, SocketMonitor &monitor) {
                SocketMonitorTask task = nullptr;
                while (monitor->isStop == 1) {
                    {
                        AutoLock l(monitor->mMutex);

                        if (monitor->mThreadNum > 1) {
                            task = monitor->mThreadLocalTasks->get(index)->takeFirst();
                        }
                        if (task == nullptr) {
                            monitor->mCurrentSockets[index] = nullptr;
                            task = monitor->mThreadPublicTasks->takeFirst();
                            if (task == nullptr) {
                                monitor->mCondition->wait(monitor->mMutex);
                                continue;
                            }

                            if (monitor->mThreadNum > 1) {
                                for (int i = 0; i < monitor->mThreadNum; i++) {
                                    if (monitor->mCurrentSockets[i] == task->sock) {
                                        monitor->mThreadLocalTasks->get(i)->putLast(task);
                                        task = nullptr;
                                        break;
                                    }
                                }

                                if (task != nullptr) {
                                    monitor->mCurrentSockets[index] = task->sock;
                                }
                            }
                        }
                    }
                    
                    //Socket will be closed directly in websocket server.
                    //We should check whether socket is still connected
                    //to prevent nullpoint exception
                    if (task != nullptr) {
                        printf("process trace1 task is not nullptr \n");
                        if(task->sock->isClosed()) {
                            task = nullptr;
                            continue;
                        }

                        SocketListener listener = nullptr;
                        {
                            printf("process trace2 task is not nullptr,fd is %d \n",task->sock->getFileDescriptor()->getFd());
                            AutoLock l(monitor->mListenerMutex);
                            listener = monitor->mListeners->get(
                                task->sock->getFileDescriptor()->getFd());    
                        }

                        if (task->event == st(NetEvent)::Disconnect) {
                            monitor->remove(task->sock);
                            task->sock->close();
                        }
                        printf("process trace3 task is not nullptr \n");
                        if (listener != nullptr) {
                            printf("process trace4 task is not nullptr \n");
                            listener->onSocketMessage(task->event, task->sock,
                                                      task->data);
                            //udp socket may be closed
                            if(task->sock->getType() == st(Socket)::Udp) {
                                task->sock->mOutputStream = nullptr;
                                task->sock->mInputStream = nullptr;
                            }
                        }
                        
                        
                        task = nullptr;
                    }
                }
                monitor = nullptr;
            },
            i, AutoClone(this));
    }
}

void _SocketMonitor::addNewSocket(Socket s, SocketListener l) {
    {
        AutoLock lock(mMutex);
        mSocks->put(s->getFileDescriptor()->getFd(), s);
    }

    {
        AutoLock lock(mListenerMutex);
        mListeners->put(s->getFileDescriptor()->getFd(), l);
    }
}

int _SocketMonitor::bind(Socket s, SocketListener l) {
    if (isSocketExist(s)) {
        return -AlreadyExists;
    }
    addNewSocket(s, l);
    s->setAsync(true);

    if (s->getType() == st(Socket)::Udp) {
        return bind(s->getFileDescriptor()->getFd(), l, true);
    } else {
        return bind(s->getFileDescriptor()->getFd(), l, false);
    }
}

int _SocketMonitor::bind(ServerSocket s, SocketListener l) {
    {
        AutoLock lock(mMutex);
        mServerSocks->put(s->getFileDescriptor()->getFd(), s);
    }
    return bind(s->getFileDescriptor()->getFd(), l, true);
}

int _SocketMonitor::bind(int fd, SocketListener l, bool isServer) {
    int serversocket = -1;
    if (isServer) {
        serversocket = fd;
    }

    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [](int fd, uint32_t events, SocketListener &listener, int serverfd,
           SocketMonitor &monitor) {
            Socket s = nullptr;
            {
                AutoLock l(monitor->mMutex);
                s = monitor->mSocks->get(fd);
                if (s == nullptr && fd != serverfd) {
                    LOG(ERROR) << "socket is null,fd is " << fd << "events is "
                               << events;
                    return st(EPollFileObserver)::OnEventRemoveObserver;
                }
            }
            if (fd == serverfd) {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                
                struct sockaddr_in6 client_address_v6;
                socklen_t client_addrLength_v6 = sizeof(struct sockaddr_in6);
                
                // may be this is udp wangsl
                if (s != nullptr && s->getType() == st(Socket)::Udp) {
                    Socket newClient = nullptr;
                    ByteArray buff = createByteArray(st(Socket)::DefaultBufferSize);

                    while (1) {
                        newClient = s->receiveFrom(buff);
                        {
                            AutoLock l(monitor->mMutex);
                            if (newClient != nullptr) {
                                monitor->mThreadPublicTasks->putLast(
                                    createSocketMonitorTask(st(NetEvent)::Message, newClient,buff));
                            }
                            monitor->mCondition->notify();
                        }

                        if (buff->size() != st(Socket)::DefaultBufferSize) {
                            break;
                        }

                        buff->quickRestore();
                    }
                    return st(EPollFileObserver)::OnEventOK;
                } else {
                    int clientfd = -1;
                    ServerSocket server = monitor->mServerSocks->get(fd);
                    s = server->accept();
                    
                    if (s != nullptr) {
                        {
                            monitor->addNewSocket(s, listener);
                            {
                                AutoLock l(monitor->mMutex);
                                monitor->mThreadPublicTasks->putLast(
                                    createSocketMonitorTask(
                                        st(NetEvent)::Connect, s));
                                monitor->mCondition->notify();
                            }
                            monitor->bind(s->getFileDescriptor()->getFd(),
                                          listener, false);
                        }
                        return st(EPollFileObserver)::OnEventOK;
                    }
                }
            }

            if ((events & EPOLLIN) != 0) {
                {
                    while (1) {
                        ByteArray buff = createByteArray(st(Socket)::DefaultBufferSize);
                        int length = s->mSock->read(buff);
                        if (length > 0) {
                            buff->quickShrink(length);
                            AutoLock l(monitor->mMutex);
                            monitor->mThreadPublicTasks->putLast(
                                createSocketMonitorTask(
                                    st(NetEvent)::Message, s, buff));
                            monitor->mCondition->notify();
                        }

                        if (length != st(Socket)::DefaultBufferSize) {
                            break;
                        }
                    }
                }
            }

            if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
                {
                    AutoLock l(monitor->mMutex);
                    monitor->mThreadPublicTasks->putLast(
                        createSocketMonitorTask(st(NetEvent)::Disconnect,s));
                    monitor->mCondition->notify();
                    return st(EPollFileObserver)::OnEventRemoveObserver;
                }
            }

            return st(EPollFileObserver)::OnEventOK;
        },
        l, serversocket, AutoClone(this));

    return 0;
}

void _SocketMonitor::close() {
    mPoll->close();
    {
        AutoLock l(mMutex);
        if(isStop == 0) {
            return;
        }

        isStop = 0;
        mThreadLocalTasks->foreach ([](LinkedList<SocketMonitorTask> &list) {
            list->clear();
            return Global::Continue;
        });

        mSocks->clear();
        mServerSocks->clear();

        mThreadPublicTasks->clear();
        mCondition->notifyAll();
    }

    {
        AutoLock l(mListenerMutex);
        mListeners->clear();
    }

    mExecutor->shutdown();
}

int _SocketMonitor::remove(Socket s) {
    {
        AutoLock lock(mMutex);
        if(isStop == 0) {
            return 0;
        }

        mSocks->remove(s->getFileDescriptor()->getFd());
        mServerSocks->remove(s->getFileDescriptor()->getFd());
    }

    {
        AutoLock lock(mListenerMutex);
        mListeners->remove(s->getFileDescriptor()->getFd());
    }

    mPoll->removeObserver(s->getFileDescriptor()->getFd());

    return 0;
}

bool _SocketMonitor::isSocketExist(Socket s) {
    AutoLock l(mMutex);
    return mSocks->get(s->getFileDescriptor()->getFd()) != nullptr;
}

_SocketMonitor::~_SocketMonitor() { delete[] mCurrentSockets; }

} // namespace obotcha