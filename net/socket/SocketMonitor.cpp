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
#include "Inspect.hpp"
#include "NetEvent.hpp"
#include "TimeWatcher.hpp"
#include "Definations.hpp"
#include "Synchronized.hpp"

namespace obotcha {

_SocketMonitorTask::_SocketMonitorTask(int event, Socket s, ByteArray data) {
    this->event = event;
    this->sock = s;
    this->data = data;
}

_SocketMonitor::_SocketMonitor() : _SocketMonitor(4) {}

_SocketMonitor::_SocketMonitor(int threadnum,int recvBuffSize) {
    mAsyncOutputPool = createAsyncOutputChannelPool();

    mRecvBuffSize = recvBuffSize;

    mMutex = createMutex();
    mClientSocks = createConcurrentHashMap<int, Socket>();
    mServerSocks = createConcurrentHashMap<int, ServerSocket>();
    //currentProcessingFds = new int[threadnum];

    mPoll = createEPollFileObserver();
    mPoll->start();
    mPendingTasks = createLinkedList<SocketMonitorTask>();
    mCondition = createCondition();

    mListeners = createConcurrentHashMap<int, SocketListener>();
    mThreadNum = threadnum;
    isStop = false;

    mThreadTaskMap = createHashMap<int,LinkedList<SocketMonitorTask>>();

    this->mExecutor = createExecutorBuilder()
                    ->setDefaultThreadNum(mThreadNum)
                    ->newThreadPool();

    for (int i = 0; i < mThreadNum; i++) {
        mExecutor->submit(
            [this](int index, SocketMonitor monitor) {
                SocketMonitorTask task = nullptr;
                int currentFd = -1;
                LinkedList<SocketMonitorTask> localTasks = createLinkedList<SocketMonitorTask>();
                
                while (!monitor->isStop) {
                    //check myself task
                    printf("eventloop start \n");
                    {
                        AutoLock l(monitor->mMutex);
                        if(currentFd != -1) {
                            task = localTasks->takeFirst();
                        }
                        printf("eventloop trace1 \n");
                        if(task == nullptr) {
                            if(currentFd != -1) {
                                mThreadTaskMap->remove(currentFd);
                                currentFd = -1;
                            }
                            while(1) {
                                task = mPendingTasks->takeFirst();
                                if(task != nullptr) {
                                    int taskFd = task->sock->getFileDescriptor()->getFd();
                                    auto tasks = mThreadTaskMap->get(taskFd);
                                    if(tasks != nullptr) {
                                        tasks->putLast(task);
                                        //mCondition->notifyAll(); //TODO:move to one thread one mutex
                                        continue;
                                    } else {
                                        mThreadTaskMap->put(taskFd,localTasks);
                                        currentFd = taskFd;
                                    }
                                }
                                break;
                            }

                            if (task == nullptr) {
                                mCondition->wait(monitor->mMutex);
                                continue;
                            }
                        }
                    }
                    printf("eventloop trace2,currentFd is %d \n",currentFd);
                    //Socket will be closed directly in websocket server.
                    //We should check whether socket is still connected
                    //to prevent nullpoint exception
                    //autoauto desc = task->sock->getFileDescriptor();
                    SocketListener listener = monitor->mListeners->get(currentFd);
                    if (listener != nullptr) {
                        printf("eventloop trace3 \n");
                        listener->onSocketMessage(task->event, task->sock,
                                                    task->data);
                    }
                    
                    if(task->event == st(NetEvent)::Disconnect) {
                        remove(task->sock->getFileDescriptor());
                        task->sock->close();
                    }
                }
                localTasks->clear();
            },
            i, AutoClone(this));
    }
}

int _SocketMonitor::bind(Socket s, SocketListener l) {
    AutoLock ll(mMutex);
    printf("bind socket!!!");
    if (isSocketExist(s)) {
        LOG(ERROR)<<"bind socket already exists!!!";
        return 0;
    }
    auto descriptor = s->getFileDescriptor();
    int fd = descriptor->getFd();
    printf("bind socket2!!!,fd is %d \n",fd);
    mClientSocks->put(fd, s);
    mListeners->put(fd, l);
    
    s->setAsync(true,mAsyncOutputPool);
    
    //descriptor->setShutdownBeforeClose(true);
    
    return bind(fd, 
                l, 
                s->getProtocol() == st(NetProtocol)::Udp);
}

int _SocketMonitor::bind(ServerSocket s, SocketListener l) {
    mServerSocks->put(s->getFileDescriptor()->getFd(), s);
    return bind(s->getFileDescriptor()->getFd(), l, true);
}

int _SocketMonitor::bind(int fd, SocketListener l, bool isServer) {
    int serversocket = isServer?fd:-1;

    mPoll->addObserver(
        fd, EPOLLIN | EPOLLRDHUP | EPOLLHUP,
        [this](int fd, uint32_t events, SocketListener &listener, int serverfd,SocketMonitor monitor) {
            Socket s = mClientSocks->get(fd);
            if (s == nullptr && fd != serverfd) {
                return st(EPollFileObserver)::OnEventRemoveObserver;
            }
            printf("socketmonitor trace1 \n");
            if (fd == serverfd) {
                // may be this is udp wangsl
                if (s != nullptr && s->getProtocol() == st(NetProtocol)::Udp) {
                    printf("socketmonitor trace2 \n");
                    Socket newClient = nullptr;
                    while (1) {
                        ByteArray buff = createByteArray(mRecvBuffSize);
                        auto stream = Cast<SocketInputStream>(s->getInputStream());
                        newClient = stream->recvDatagram(buff);
                        printf("socketmonitor trace3 \n");
                        bind(newClient,listener);//TODO?????
                        if(newClient == nullptr) {
                            //LOG(ERROR)<<"SocketMonitor accept udp is a null socket!!!!";
                            break;
                        }
                        Synchronized(mMutex){
                            mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Message, newClient,buff));
                            mCondition->notify();
                        }

                        if (buff->size() != mRecvBuffSize) {
                            break;
                        }
                    }
                } else {
                    int clientfd = -1;
                    ServerSocket server = mServerSocks->get(fd);
                    s = server->accept();
                    if (s != nullptr) {
                        bind(s,listener);
                        Synchronized(mMutex){
                            mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Connect, s));
                            mCondition->notify();
                        }
                    } else {
                        LOG(ERROR)<<"SocketMonitor accept socket is a null socket!!!!";
                    }
                }
                return st(EPollFileObserver)::OnEventOK;
            }

            if ((events & EPOLLIN) != 0) {
                //auto sock = s->getSockImpl();
                auto inputStream = s->getInputStream();
                if(inputStream != nullptr) {
                    while (1) {
                        ByteArray buff = createByteArray(mRecvBuffSize);
                        //int length = sock->read(buff);
                        long length = inputStream->read(buff);
                        if (length > 0) {
                            buff->quickShrink(length);
                            AutoLock l(mMutex);
                            mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Message, s, buff));
                            mCondition->notify();
                        }

                        if (length != mRecvBuffSize) {
                            break;
                        }
                    }
                }
            }

            if ((events & (EPOLLRDHUP | EPOLLHUP)) != 0) {
                //s->getFileDescriptor()->setShutdownBeforeClose(false);
                AutoLock l(mMutex);
                mPendingTasks->putLast(createSocketMonitorTask(st(NetEvent)::Disconnect, s));
                mCondition->notify();

                return st(EPollFileObserver)::OnEventRemoveObserver;
            }
            return st(EPollFileObserver)::OnEventOK;
        },
        l, serversocket, AutoClone(this));

    return 0;
}

void _SocketMonitor::close() {
    mPoll->close();
    Synchronized(mMutex) {
        Inspect(isStop);
        isStop = true;

        mPendingTasks->clear();
        mCondition->notifyAll();
    }

    mClientSocks->clear();
    mServerSocks->clear();

    mListeners->clear();
    mExecutor->shutdown();
    mExecutor->awaitTermination();

    if(mAsyncOutputPool != nullptr) {
        mAsyncOutputPool->close();
    }
}

void _SocketMonitor::dump() {
    printf("---SocketMonitor dump start --- \n");
    printf("mSocks size is %d \n",mClientSocks->size());
    mPoll->dump();
    printf("---SocketMonitor dump end --- \n");
}

int _SocketMonitor::unbind(Socket s) {
    AutoLock l(mMutex);
    //s->getFileDescriptor()->setShutdownBeforeClose(false);
    remove(s->getFileDescriptor());
    return 0;
}

int _SocketMonitor::unbind(ServerSocket s) {
    AutoLock l(mMutex);
    //s->getFileDescriptor()->setShutdownBeforeClose(false);
    remove(s->getFileDescriptor());
    return 0;
}

int _SocketMonitor::remove(FileDescriptor fd) {
    if(fd != nullptr) {
        mPoll->removeObserver(fd->getFd());
        mClientSocks->remove(fd->getFd());
        mServerSocks->remove(fd->getFd());
        mListeners->remove(fd->getFd());
    }
    return 0;
}

bool _SocketMonitor::isSocketExist(Socket s) {
    //auto descriptor = s->getFileDescriptor();
    int fd = s->getFileDescriptor()->getFd();
    return mClientSocks->get(fd) != nullptr;
}

_SocketMonitor::~_SocketMonitor() {
    //delete[]currentProcessingFds;
}

} // namespace obotcha
