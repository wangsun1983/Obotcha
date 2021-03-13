#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <stddef.h>

#include "SocketMonitor.hpp"
#include "ExecutorBuilder.hpp"

namespace obotcha {

_SocketMonitorTask::_SocketMonitorTask(int event,Socket s,ByteArray data) {
    this->event = event;
    this->sock = s;
    this->data = data;
}

_SocketMonitor::_SocketMonitor():_SocketMonitor(1) {
}

_SocketMonitor::_SocketMonitor(int threadnum) {
    mMutex = createMutex();
    mSocks = createHashMap<int,Socket>();

    mPoll = createEPollFileObserver();
    mPoll->start();
    mThreadPublicTasks = createLinkedList<SocketMonitorTask>();
    mThreadLocalTasks = createArrayList<LinkedList<SocketMonitorTask>>();
    mCurrentSockets = new Socket[threadnum];
    mCondition = createCondition();

    mListenerMutex = createMutex();
    mListeners = createHashMap<int,SocketListener>();
    mThreadNum = threadnum;
    isStop = 1;

    for(int i = 0;i < threadnum;i++) {
        mThreadLocalTasks->add(createLinkedList<SocketMonitorTask>());
    }

    this->mExecutor = createExecutorBuilder()->setThreadNum(mThreadNum)->newThreadPool();
    for(int i = 0;i < mThreadNum;i++) {
        mExecutor->execute([](int index,
                            SocketMonitor &monitor) {
            SocketMonitorTask task = nullptr;
            //printf("thread1 trace1 \n");
            while(monitor->isStop == 1) {
                //printf("thread1 trace2 \n");
                {
                    AutoLock l(monitor->mMutex);
                    task = monitor->mThreadLocalTasks->get(index)->deQueueFirst();
                    if(task == nullptr) {
                        monitor->mCurrentSockets[index] = nullptr;
                        task = monitor->mThreadPublicTasks->deQueueFirst();
                        if(task == nullptr) {
                            monitor->mCondition->wait(monitor->mMutex);
                            continue;
                        }

                        for(int i = 0;i<monitor->mThreadNum;i++) {
                            if(monitor->mCurrentSockets[i] == task->sock) {
                                monitor->mThreadLocalTasks->get(i)->enQueueLast(task);
                                task = nullptr;
                                break;
                            }
                        }

                        if(task != nullptr) {
                            monitor->mCurrentSockets[index] = task->sock;
                        }
                    }
                }
                
                //printf("thread1 trace3 \n");
                if(task != nullptr) {
                    SocketListener listener = nullptr;
                    {
                        AutoLock l(monitor->mListenerMutex);
                        listener = monitor->mListeners->get(task->sock->getFd());
                    }
                    if(listener != nullptr) {
                        listener->onSocketMessage(task->event,task->sock,task->data);
                        //printf("onSocketmessgae fd is %d \n",task->sock->getFd());
                        if(task->event == st(Socket)::Disconnect) {
                            monitor->remove(task->sock);
                            task->sock->close();
                        }
                    }
                }
                //printf("thread1 trace4 \n");
            }
            //printf("thread1 trace5 \n");
            monitor = nullptr;
        },
        i,
        AutoClone(this));
    }
}

void _SocketMonitor::addNewSocket(Socket s,SocketListener l) {
    {
        AutoLock lock(mMutex);
        mSocks->put(s->getFd(),s);
    }

    {
        AutoLock lock(mListenerMutex);
        mListeners->put(s->getFd(),l);
    }
}

int _SocketMonitor::bind(Socket s,SocketListener l) {
    if(isSocketExist(s)) {
        return -AlreadyExists;
    }

    return bind(s->getFd(),l,false);
}


int _SocketMonitor::bind(ServerSocket s,SocketListener l) {
    return bind(s->getFd(),l,true);
}

int _SocketMonitor::bind(int fd,SocketListener l,bool isServer) {
    //printf("bind fd is %d \n",fd);
    int serversocket = -1;
    if(isServer) {
        serversocket = fd;
    }

    mPoll->addObserver(fd,
                        EPOLLIN|EPOLLRDHUP|EPOLLHUP,
                        [](int fd,
                           uint32_t events,
                           ByteArray data,
                           SocketListener &listener,
                           int serverfd,
                           SocketMonitor &monitor) {
        //if(data != nullptr) {
        //    printf("observer trace1 data is %s\n",data->toString()->toChars());
        //}
        if(fd == serverfd) {
            struct sockaddr_in client_address;
            socklen_t client_addrLength = sizeof(struct sockaddr_in);
            int clientfd = accept(fd,( struct sockaddr* )&client_address, &client_addrLength );
            if(clientfd != -1) {
                Socket s = createSocket(clientfd);
                s->setInetAddress(createInetAddress(
                                    createString(inet_ntoa(client_address.sin_addr)),
                                    ntohs(client_address.sin_port)));
                {
                    monitor->addNewSocket(s,listener);
                    {
                        AutoLock l(monitor->mMutex);
                        monitor->mThreadPublicTasks->enQueueLast(createSocketMonitorTask(st(Socket)::Connect,s));
                        monitor->mCondition->notify();
                    }
                    monitor->bind(s->getFd(),listener,false);
                }
                return st(EPollFileObserver)::OnEventOK;
            }
        }

        Socket s = nullptr;
        {
            AutoLock l(monitor->mMutex);
            s = monitor->mSocks->get(fd);
        }

        //if(s == nullptr) {
            //printf("i can not find socket ,fd is %d ,events is %x\n",fd,events);
            //return st(EPollFileObserver)::OnEventOK;
        //}
        
        if((events & EPOLLHUP) != 0) {
            //printf("observer trace2 \n");
            return st(EPollFileObserver)::OnEventRemoveObserver;
        } 

        if((events & EPOLLRDHUP)!= 0) {
            {
                //printf("disconnect fd is %d \n",fd);
                AutoLock l(monitor->mMutex);
                monitor->mThreadPublicTasks->enQueueLast(createSocketMonitorTask(st(Socket)::Disconnect,s));
                monitor->mCondition->notify();
                return st(EPollFileObserver)::OnEventRemoveObserver;
            }
        }
        
        if((events & EPOLLIN) != 0) {
            {   
                //printf("ondata fd is %d \n",fd);
                if(data != nullptr && data->size() != 0) {
                    AutoLock l(monitor->mMutex);
                    monitor->mThreadPublicTasks->enQueueLast(createSocketMonitorTask(st(Socket)::Message,s,data));
                    monitor->mCondition->notify();
                }
            }
        }
        
        return st(EPollFileObserver)::OnEventOK;
        
    },l,serversocket,AutoClone(this));

    return 0;
}


void _SocketMonitor::release() {
    mPoll->release();
    isStop = 0;
    {
        AutoLock l(mMutex);
        mThreadLocalTasks->foreach([](LinkedList<SocketMonitorTask> &list){
            list->clear();
            return 1;
        });

        mSocks->clear();

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
    //printf("remove fd is %d \n",s->getFd());
    {
        AutoLock lock(mMutex);
        mSocks->remove(s->getFd());
    }

    {
        AutoLock lock(mListenerMutex);
        mListeners->remove(s->getFd());
    }

    return 0;
}

bool _SocketMonitor::isSocketExist(Socket s) {
    AutoLock l(mMutex);
    return mSocks->get(s->getFd()) != nullptr;
}

_SocketMonitor::~_SocketMonitor() {
    delete []mCurrentSockets;
}

}