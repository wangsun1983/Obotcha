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
#include "TimeWatcher.hpp"

namespace obotcha {

_SocketMonitorTask::_SocketMonitorTask(int event, Socket s, ByteArray data) {
    this->event = event;
    this->sock = s;
    this->data = data;
}

_SocketMonitor::_SocketMonitor() : _SocketMonitor(1) {}

_SocketMonitor::_SocketMonitor(int threadnum) {
    mMutex = createMutex();
    mSocks = createConcurrentHashMap<int, Socket>();
    mServerSocks = createConcurrentHashMap<int, ServerSocket>();
    currentProcessingFds = new int[threadnum];

    mPoll = createEPollFileObserver();
    mPoll->start();
    mThreadPublicTasks = createLinkedList<SocketMonitorTask>();
    mCondition = createCondition();

    mListeners = createConcurrentHashMap<int, SocketListener>();
    mThreadNum = threadnum;
    isStop = 1;

    for(int i = 0;i < threadnum;i++) {
        currentProcessingFds[i] = -1;
    }

    this->mExecutor =
        createExecutorBuilder()->setThreadNum(mThreadNum)->newThreadPool();

    for (int i = 0; i < mThreadNum; i++) {
        mExecutor->submit(
            [](int index, SocketMonitor &monitor) {
                SocketMonitorTask task = nullptr;
                while (monitor->isStop == 1) {
                    {
                        AutoLock l(monitor->mMutex);
                        auto iterator = monitor->mThreadPublicTasks->getIterator();
                        while(iterator->hasValue()) {
                            task = iterator->getValue();
                            auto desc = task->sock->getFileDescriptor();
                            if(desc != nullptr) {
                                int fd = desc->getFd();
                                bool found = false;
                                for(int i = 0;i<monitor->mThreadNum;i++) {
                                    if(monitor->currentProcessingFds[i] == fd) {
                                        found = true;
                                        break;
                                    }
                                }

                                if(found) {
                                    iterator->next();
                                    task = nullptr;
                                    continue;
                                } else {
                                    monitor->currentProcessingFds[index] = fd;
                                    iterator->remove();
                                }
                            }
                            break;
                        }

                        if (task == nullptr) {
                            monitor->mCondition->wait(monitor->mMutex);
                            continue;
                        }
                    }
                    
                    //Socket will be closed directly in websocket server.
                    //We should check whether socket is still connected
                    //to prevent nullpoint exception
                    if (task != nullptr) {
                        auto desc = task->sock->getFileDescriptor();
                        if(task->sock->isClosed()) {
                            {
                                if(desc != nullptr) {
                                    AutoLock l(monitor->mMutex);
                                    monitor->currentProcessingFds[index] = -1;
                                }
                            }
                            task = nullptr;
                            continue;
                        }
                        
                        SocketListener listener = monitor->mListeners
                                                         ->get(task->sock->getFileDescriptor()->getFd());    
                        if (listener != nullptr) {
                            listener->onSocketMessage(task->event, task->sock,
                                                      task->data);
                            //udp socket may be closed
                            if(task->sock->getProtocol() == st(Socket)::Protocol::Udp) {
                                task->sock->mOutputStream = nullptr;
                                task->sock->mInputStream = nullptr;
                            }
                        }

                        if(task->event == st(NetEvent)::Disconnect) {
                            monitor->_remove(desc);
                            task->sock->close();
                        }
                        
                        {
                            AutoLock l(monitor->mMutex);
                            monitor->currentProcessingFds[index] = -1;
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
    mSocks->put(s->getFileDescriptor()->getFd(), s);
    mListeners->put(s->getFileDescriptor()->getFd(), l);
}

int _SocketMonitor::bind(Socket s, SocketListener l) {
    AutoLock ll(mMutex);

    if (isSocketExist(s)) {
        LOG(ERROR)<<"bind socket already exists!!!";
        return 0;
    }

    addNewSocket(s,l);
    s->setAsync(true);

    if (s->getProtocol() == st(Socket)::Protocol::Udp) {
        return bind(s->getFileDescriptor()->getFd(), l, true);
    } else {
        return bind(s->getFileDescriptor()->getFd(), l, false);
    }
}

int _SocketMonitor::bind(ServerSocket s, SocketListener l) {
    mServerSocks->put(s->getFileDescriptor()->getFd(), s);
    return bind(s->getFileDescriptor()->getFd(), l, true);
}

AtomicInteger cc = createAtomicInteger(0);

int _SocketMonitor::bind(int fd, SocketListener l, bool isServer) {
    int serversocket = -1;
    if (isServer) {
        serversocket = fd;
    }
   
    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [](int fd, uint32_t events, SocketListener &listener, int serverfd,SocketMonitor &monitor) {
            Socket s = monitor->mSocks->get(fd);
            if (s == nullptr && fd != serverfd) {
                return st(EPollFileObserver)::OnEventRemoveObserver;
            }
            
            if (fd == serverfd) {
                // may be this is udp wangsl
                if (s != nullptr && s->getProtocol() == st(Socket)::Protocol::Udp) {
                    Socket newClient = nullptr;
                    while (1) {
                        ByteArray buff = createByteArray(st(Socket)::DefaultBufferSize);
                        newClient = s->receiveFrom(buff);
                        if(newClient == nullptr) {
                            LOG(ERROR)<<"SocketMonitor accept udp is a null socket!!!!";
                            break;
                        }

                        {
                            AutoLock l(monitor->mMutex);
                            monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Message, newClient,buff));
                            monitor->mCondition->notify();
                        }

                        if (buff->size() != st(Socket)::DefaultBufferSize) {
                            break;
                        }
                    }
                } else {
                    int clientfd = -1;
                    ServerSocket server = monitor->mServerSocks->get(fd);
                    s = server->accept();
                    monitor->bind(s,listener);
                    if (s != nullptr) {
                        {
                            AutoLock l(monitor->mMutex);
                            monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Connect, s));
                            monitor->mCondition->notify();
                        }
                    } else {
                        LOG(ERROR)<<"SocketMonitor accept socket is a null socket!!!!";
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
                            monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Message, s, buff));
                            monitor->mCondition->notify();
                        }

                        if (length != st(Socket)::DefaultBufferSize) {
                            break;
                        }
                    }
                }
            }

            if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
                AutoLock l(monitor->mMutex);
                monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Disconnect, s));
                monitor->mCondition->notify();

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

        mThreadPublicTasks->clear();
        mCondition->notifyAll();
    }

    mSocks->clear();
    mServerSocks->clear();
    
    mListeners->clear();
    mExecutor->shutdown();
}

int _SocketMonitor::remove(Socket s,bool isClose) {
    AutoLock l(mMutex);
    if(isClose) {
        mThreadPublicTasks->putLast(createSocketMonitorTask(st(NetEvent)::Disconnect,s));
        mCondition->notify();
    } else {
        _remove(s->getFileDescriptor());
    }
    
    return 0;
}

int _SocketMonitor::_remove(FileDescriptor fd) {
    if(fd == nullptr) {
        return 0;
    }
    
    {
        AutoLock lock(mMutex);
        mPoll->removeObserver(fd->getFd());
    }
    mSocks->remove(fd->getFd());
    mServerSocks->remove(fd->getFd());

    mListeners->remove(fd->getFd());

    return 0;

}

bool _SocketMonitor::isSocketExist(Socket s) {
    auto descriptor = s->getFileDescriptor();
    return mSocks->get(descriptor->getFd()) != nullptr;
}

_SocketMonitor::~_SocketMonitor() {
    delete[]currentProcessingFds;
}

} // namespace obotcha