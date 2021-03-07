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


_SocketMonitorTask::_SocketMonitorTask(int event,Socket s):_SocketMonitorTask(event,s,nullptr) {
}

_SocketMonitorTask::_SocketMonitorTask(int event,Socket s,ByteArray data) {
    this->event = event;
    this->sock = s;
    this->data = data;
}

_SocketMonitor::_SocketMonitor():_SocketMonitor(1) {
}

_SocketMonitor::_SocketMonitor(int threadnum) {
    mServerSockFd = -1;
    mMutex = createMutex();
    mSocks = createHashMap<int,Socket>();

    mPoll = createEPollFileObserver();
    mPoll->start();
    mThreadNum = 1;

    mThreadPublicTasks = createLinkedList<SocketMonitorTask>();
    mThreadLocalTasks = createArrayList<LinkedList<SocketMonitorTask>>(threadnum);
    mCurrentSockets = new Socket[threadnum];
    mCondition = createCondition();

    for(int i = 0;i < threadnum;i++) {
        mThreadLocalTasks->add(createLinkedList<SocketMonitorTask>());
    }

    mThreadNum = threadnum;

    isStop = 1;
}

int _SocketMonitor::bind(Socket s,SocketListener l) {
    {
        AutoLock l(mMutex);
        mSocks->put(s->getFd(),s);
    }
    return bind(s->getFd(),l);
}

int _SocketMonitor::bind(ServerSocket s,SocketListener l) {
    mServerSockFd = s->getFd();
    {
        AutoLock l(mMutex);
        mSocks->put(s->getFd(),s);
    }
    return bind(s->getFd(),l);
}

int _SocketMonitor::bind(int fd,SocketListener l) {
    mPoll->addObserver(fd,
                        EPOLLIN|EPOLLRDHUP|EPOLLHUP,
                        [](int fd,
                           uint32_t events,
                           ByteArray data,
                           SocketListener &listener,
                           int sockfd,
                           Mutex mutex,
                           Condition cond,
                           HashMap<int,Socket> socks,
                           LinkedList<SocketMonitorTask> &tasks) {
        if(fd == sockfd) {
            struct sockaddr_in client_address;
            socklen_t client_addrLength = sizeof(struct sockaddr_in);
            int clientfd = accept(fd,( struct sockaddr* )&client_address, &client_addrLength );
            if(clientfd != -1) {
                Socket s = createSocket(clientfd);
                s->setInetAddress(createInetAddress(
                                    createString(inet_ntoa(client_address.sin_addr)),
                                    ntohs(client_address.sin_port)));
                {
                    AutoLock l(mutex);
                    socks->put(clientfd,s);
                    tasks->enQueueLast(createSocketMonitorTask(st(Socket)::Connect,s));
                    cond->notifyAll();
                }
                return st(EPollFileObserver)::OnEventOK;
            }
        }

        Socket s = nullptr;
        {
            AutoLock l(mutex);
            s = socks->get(fd);
        }
        
        if((events & (EPOLLHUP|EPOLLRDHUP))!= 0) {
            {
                AutoLock l(mutex);
                socks->remove(fd);
                tasks->enQueueLast(createSocketMonitorTask(st(Socket)::Disconnect,s));
                cond->notifyAll();
            }
        } else if((events & EPOLLIN) != 0) {
            {
                AutoLock l(mutex);
                tasks->enQueueLast(createSocketMonitorTask(st(Socket)::Message,s,data));
                cond->notifyAll();
            }
        }
        
        return st(EPollFileObserver)::OnEventOK;
        
    },l,mServerSockFd,mMutex,mCondition,mSocks,mThreadPublicTasks);


    this->mExecutor = createExecutorBuilder()->setThreadNum(mThreadNum)->newThreadPool();
    for(int i = 0;i < mThreadNum;i++) {
        mExecutor->execute([](Mutex mutex,
                                    Condition cond,
                                    int index,
                                    int totalnum,
                                    ArrayList<LinkedList<SocketMonitorTask>> &localtasks,
                                    LinkedList<SocketMonitorTask> &publictasks,
                                    Socket *currentSocks,
                                    SocketListener &listener,
                                    int32_t *stop) {
            while(*stop == 1){
                SocketMonitorTask task = nullptr;
                {
                    AutoLock l(mutex);
                    task = localtasks->get(index)->deQueueFirst();
                    if(task == nullptr) {
                        currentSocks[index] = nullptr;
                        task = publictasks->deQueueFirst();
                        if(task == nullptr) {
                            cond->wait(mutex);
                            continue;
                        }

                        bool isOtherThreadTask = false;
                        for(int i = 0;i<totalnum;i++) {
                            if(currentSocks[i] == task->sock) {
                                localtasks->get(i)->enQueueLast(task);
                                task = nullptr;
                                isOtherThreadTask = true;
                                cond->notifyAll();
                                break;
                            }
                        }

                        if(isOtherThreadTask) {
                            continue;
                        }
                    }
                }
                
                listener->onSocketMessage(task->event,task->sock,task->data);
            }
            
        },
        mMutex,
        mCondition,
        i,
        mThreadNum,
        mThreadLocalTasks,
        mThreadPublicTasks,
        mCurrentSockets,
        l,
        (int32_t *)&isStop);
    }
    
    return 0;
}


void _SocketMonitor::release() {
    mPoll->release();
    isStop = 0;
    {
        AutoLock l(mMutex);
        ListIterator<LinkedList<SocketMonitorTask>> iterator = mThreadLocalTasks->getIterator();
        while(iterator->hasValue()) {
            LinkedList<SocketMonitorTask> ll = iterator->getValue();
            ll->clear();
            iterator->next();
        }

        mSocks->clear();

        mThreadPublicTasks->clear();
        mCondition->notifyAll();
    }

    mExecutor->shutdown();
}

int _SocketMonitor::remove(Socket s) {
    return mPoll->removeObserver(s->getFd());
}

_SocketMonitor::~_SocketMonitor() {
    delete []mCurrentSockets;
}

}