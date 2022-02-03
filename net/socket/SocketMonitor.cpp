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
                                        monitor->mCondition->notifyAll();
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
                        if(task->sock->isClosed()) {
                            task = nullptr;
                            continue;
                        }

                        SocketListener listener = nullptr;
                        {
                            AutoLock l(monitor->mListenerMutex);
                            listener = monitor->mListeners->get(task->sock->getFileDescriptor()->getFd());    
                        }

                        if (listener != nullptr) {
                            listener->onSocketMessage(task->event, task->sock,
                                                      task->data);
                            //udp socket may be closed
                            if(task->sock->getType() == st(Socket)::Udp) {
                                task->sock->mOutputStream = nullptr;
                                task->sock->mInputStream = nullptr;
                            }
                        } else {
                            printf("no listener1!!! \n");
                        }

                        if(task->event == st(NetEvent)::Disconnect) {
                            //printf("close socket!!!! \n");
                            monitor->_remove(task->sock);
                            task->sock->close();
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
    AutoLock ll(mMutex);

    if (isSocketExist(s)) {
        LOG(ERROR)<<"bind socket already exists!!!";
        return -AlreadyExists;
    }
    addNewSocket(s,l);
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

AtomicInteger cc = createAtomicInteger(0);

int _SocketMonitor::bind(int fd, SocketListener l, bool isServer) {
    int serversocket = -1;
    if (isServer) {
        serversocket = fd;
    }

    AutoLock lock(mMutex);     
    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [](int fd, uint32_t events, SocketListener &listener, int serverfd,SocketMonitor &monitor) {
            Socket s = nullptr;
            {
                AutoLock l(monitor->mMutex);
                s = monitor->mSocks->get(fd);
                if (s == nullptr && fd != serverfd) {
                    //LOG(ERROR) << "socket is null,fd is " << fd << "events is "
                    //           << events;
                    return st(EPollFileObserver)::OnEventRemoveObserver;
                }
            }
            if (fd == serverfd) {
                // may be this is udp wangsl
                if (s != nullptr && s->getType() == st(Socket)::Udp) {
                    Socket newClient = nullptr;
                    ByteArray buff = createByteArray(st(Socket)::DefaultBufferSize);

                    while (1) {
                        newClient = s->receiveFrom(buff);
                        {
                            AutoLock l(monitor->mMutex);
                            if (newClient != nullptr) {
                                monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Message, newClient,buff));
                            }
                            monitor->mCondition->notifyAll();
                        }

                        if (buff->size() != st(Socket)::DefaultBufferSize) {
                            break;
                        }

                        buff->quickRestore();
                    }
                } else {
                    int clientfd = -1;
                    ServerSocket server = monitor->mServerSocks->get(fd);
                    s = server->accept();
                    monitor->bind(s,listener);

                    if (s != nullptr) {
                        {
                            //AutoLock l(monitor->mMutex);
                            //monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Connect, s));
                            //monitor->mCondition->notifyAll();
                            listener->onSocketMessage(st(NetEvent)::Connect,s,nullptr);
                        }
                    }
                }
                return st(EPollFileObserver)::OnEventOK;
            }
            
            if ((events & EPOLLIN) != 0) {
                auto sock = s->getSockImpl();
                if(sock != nullptr) {
                    while (1) {
                        ByteArray buff = createByteArray(st(Socket)::DefaultBufferSize);
                        int length = sock->read(buff);
                        if (length > 0) {
                            buff->quickShrink(length);
                            AutoLock l(monitor->mMutex);
                            listener->onSocketMessage(st(NetEvent)::Message,s,
                                                      buff);
                            //monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Message, s, buff));
                            //monitor->mCondition->notifyAll();
                        }

                        if(length == -1) {
                            printf("i read -1!!! \n");
                        }
                        if (length != st(Socket)::DefaultBufferSize) {
                            break;
                        }
                    }
                } else {
                    printf("sock is closed in epoll!!! \n");
                }
            }

            if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
                //int v = cc->addAndGet(1);
                //printf("v is %ld \n",s->getTag());
                //AutoLock l(monitor->mMutex);
                //monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Disconnect,s));
                //monitor->mCondition->notifyAll();
                //if(monitor->mSocks->get(s->getFileDescriptor()->getFd))
                if(!s->isClosed()) {
                    listener->onSocketMessage(st(NetEvent)::Disconnect,s,nullptr);
                }
                //printf("[this is %p],hungup socket,fd is %d \n",monitor.get_pointer(),s->getFileDescriptor()->getFd());
                return st(EPollFileObserver)::OnEventRemoveObserver;
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

int _SocketMonitor::remove(Socket s,bool isClose) {
    AutoLock l(mMutex);
    if(isClose) {
        //mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Disconnect,s));
        //mCondition->notifyAll();
        _remove(s);
        s->close();
    } else {
        _remove(s);
    }
    
    return 0;
}

int _SocketMonitor::_remove(Socket s) {
    if(s->isClosed()) {
        //printf("closed!!! \n");
        return 0;
    }
    
    auto fileDescriptor = s->getFileDescriptor();
    {
        AutoLock lock(mMutex);
        auto sock = mSocks->get(fileDescriptor->getFd());
        if(sock != nullptr && sock->getTag() != s->getTag()) {
            LOG(ERROR)<<"remove different socket!!!";
            return 0;
        }

        mPoll->removeObserver(fileDescriptor->getFd());
        mSocks->remove(fileDescriptor->getFd());
        mServerSocks->remove(fileDescriptor->getFd());
    }

    {
        AutoLock lock(mListenerMutex);
        mListeners->remove(fileDescriptor->getFd());
    }
    return 0;
}

bool _SocketMonitor::isSocketExist(Socket s) {
    auto descriptor = s->getFileDescriptor();
    return mSocks->get(descriptor->getFd()) != nullptr;
}

void _SocketMonitor::dump() {
    for (int i = 0; i < mThreadNum; i++) {
        printf("local task[%d] size is %d \n",i,mThreadLocalTasks->get(i)->size());
    }

    printf("public task size is %d \n",mThreadPublicTasks->size());
}

_SocketMonitor::~_SocketMonitor() { delete[] mCurrentSockets; }

} // namespace obotcha