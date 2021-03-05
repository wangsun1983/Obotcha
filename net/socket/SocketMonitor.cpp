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

namespace obotcha {


_SocketMonitorTask::_SocketMonitorTask(int event,Socket s) {
    this->event = event;
    this->sock = s;
}

_SocketMonitorTask::_SocketMonitorTask(int event,Socket s,ByteArray data) {
    this->event = event;
    this->sock = s;
    this->data = data;
}

_SocketMonitor::_SocketMonitor() {
    mServerSockFd = -1;
    mMutex = createMutex();
    mSocks = createHashMap<int,Socket>();

    mPoll = createEPollFileObserver();
    mPoll->start();
    mThreadNum = 1;
}

_SocketMonitor::_SocketMonitor(int threadnum):_SocketMonitor() {
    mThreadPublicTasks = createLinkedList<SocketMonitorTask>();
    mThreadLocalTasks = createArrayList<LinkedList<SocketMonitorTask>>(threadnum);
    mCurrentSockets = new Socket[threadnum];
    mCondition = createCondition();

    for(int i = 0;i < threadnum;i++) {
        mThreadLocalTasks->add(createLinkedList<SocketMonitorTask>());
    }

    mThreadNum = threadnum;
}

int _SocketMonitor::bind(Socket s,SocketListener l) {
    bind(s->getFd(),l);
}

int _SocketMonitor::bind(ServerSocket s,SocketListener l) {
    mServerSockFd = s->getFd();
    bind(s->getFd(),l);
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
                    tasks->enQueueLast(createSocketMonitorTask(st(SocketMonitorTask)::Connect,s));
                    cond->notifyAll();
                }
                
                //listener->onConnect(s);
                return st(EPollFileObserver)::OnEventOK;
            }
        }

        Socket s = nullptr;
        {
            AutoLock l(mutex);
            s = socks->get(fd);
        }
        
        if((events & (EPOLLHUP|EPOLLRDHUP))!= 0) {
            //listener->onDisconnect(s);
            {
                AutoLock l(mutex);
                socks->remove(fd);
                tasks->enQueueLast(createSocketMonitorTask(st(SocketMonitorTask)::Disconnect,s));
            }
        } else if((events & EPOLLIN) != 0) {
            //listener->onDataReceived(s,data);
            {
                AutoLock l(mutex);
                tasks->enQueueLast(createSocketMonitorTask(st(SocketMonitorTask)::Disconnect,s,data));
            }
        } 
        
    },l,mServerSockFd,mMutex,mCondition,mSocks,mThreadPublicTasks);


    mThreads = createArrayList<Thread>(mThreadNum);
    for(int i = 0;i < mThreadNum;i++) {
        Thread th = createThread([](Mutex mutex,
                                    Condition cond,
                                    int index,
                                    int totalnum,
                                    ArrayList<LinkedList<SocketMonitorTask>> &localtasks,
                                    LinkedList<SocketMonitorTask> &publictasks,
                                    Socket *currentSocks,
                                    SocketListener &listener) {
            while(1){
                SocketMonitorTask task = nullptr;
                {
                    AutoLock l(mutex);
                    task = localtasks->get(index)->deQueueFirst();
                    if(task == nullptr) {
                        currentSocks[index] = nullptr;
                        task = publictasks->deQueueFirst();
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

                        if(task == nullptr) {
                            cond->wait(mutex);
                            continue;
                        }
                    }
                }

                switch(task->event) {
                    case st(SocketMonitorTask)::Connect:
                        listener->onConnect(task->sock);
                    break;

                    case st(SocketMonitorTask)::Message:
                        listener->onDataReceived(task->sock,task->data);
                    break;

                    case st(SocketMonitorTask)::Disconnect:
                        listener->onDisconnect(task->sock);
                    break;
                }

            }
            
        },mMutex,
        mCondition,
        i,
        mThreadNum,
        mThreadLocalTasks,
        mThreadPublicTasks,
        mCurrentSockets,
        l);

        th->start();
        mThreads->add(th);
    }
    
    return -1;
}


void _SocketMonitor::release() {
    mPoll->release();
}

int _SocketMonitor::remove(Socket s) {
    return mPoll->removeObserver(s->getFd());
}

}