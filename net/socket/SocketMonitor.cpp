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
#include "Log.hpp"

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
    mServerSocks = createHashMap<int,ServerSocket>();

    mPoll = createEPollFileObserver();
    mPoll->start();
    mThreadPublicTasks = createLinkedList<SocketMonitorTask>();
    mThreadLocalTasks = createArrayList<LinkedList<SocketMonitorTask>>();
    mCurrentSockets = new Socket[threadnum];
    mCondition = createCondition();

    mListenerMutex = createSpinLock();
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
            while(monitor->isStop == 1) {
                {
                    AutoLock l(monitor->mMutex);
                    
                    if(monitor->mThreadNum > 1) {
                        task = monitor->mThreadLocalTasks->get(index)->takeFirst();
                    }
                    if(task == nullptr) {
                        monitor->mCurrentSockets[index] = nullptr;
                        task = monitor->mThreadPublicTasks->takeFirst();
                        if(task == nullptr) {
                            monitor->mCondition->wait(monitor->mMutex);
                            continue;
                        }
                        
                        if(monitor->mThreadNum > 1) {
                            for(int i = 0;i<monitor->mThreadNum;i++) {
                                if(monitor->mCurrentSockets[i] == task->sock) {
                                    monitor->mThreadLocalTasks->get(i)->putLast(task);
                                    task = nullptr;
                                    break;
                                }
                            }

                            if(task != nullptr) {
                                monitor->mCurrentSockets[index] = task->sock;
                            }
                        }
                    }
                }

                if(task != nullptr) {
                    SocketListener listener = nullptr;
                    {
                        AutoLock l(monitor->mListenerMutex);
                        listener = monitor->mListeners->get(task->sock->getFileDescriptor()->getFd());
                    }
                    if(listener != nullptr) {
                        listener->onSocketMessage(task->event,task->sock,task->data);
                        if(task->event == st(SocketListener)::Disconnect) {
                            monitor->remove(task->sock);
                            task->sock->close();
                        }
                    }
                    task = nullptr;
                }
            }
            monitor = nullptr;
        },
        i,
        AutoClone(this));
    }
}

void _SocketMonitor::addNewSocket(Socket s,SocketListener l) {
    {
        AutoLock lock(mMutex);
        mSocks->put(s->getFileDescriptor()->getFd(),s);
    }

    {
        AutoLock lock(mListenerMutex);
        mListeners->put(s->getFileDescriptor()->getFd(),l);
    }
}

int _SocketMonitor::bind(Socket s,SocketListener l) {
    if(isSocketExist(s)) {
        return -AlreadyExists;
    }
    addNewSocket(s,l);
    s->setAsync(true);

    if(s->getType() == st(Socket)::Udp) {
        return bind(s->getFileDescriptor()->getFd(),l,true);
    } else {
        return bind(s->getFileDescriptor()->getFd(),l,false);
    }
}


int _SocketMonitor::bind(ServerSocket s,SocketListener l) {
    {
        AutoLock lock(mMutex);
        mServerSocks->put(s->getFileDescriptor()->getFd(),s);
    }
    return bind(s->getFileDescriptor()->getFd(),l,true);
}

int _SocketMonitor::bind(int fd,SocketListener l,bool isServer) {
    int serversocket = -1;
    if(isServer) {
        serversocket = fd;
    }

    mPoll->addObserver(fd,
                        EPOLLIN|EPOLLRDHUP|EPOLLHUP,
                        [](int fd,
                           uint32_t events,
                           SocketListener &listener,
                           int serverfd,
                           SocketMonitor &monitor) {
        //printf("fd is %d,serverfd is %d,events is %x \n",fd,serverfd,events);
        Socket s = nullptr;
        {
            AutoLock l(monitor->mMutex);
            s = monitor->mSocks->get(fd);
            if(s == nullptr && fd != serverfd) {
                LOG(ERROR)<<"socket is null,fd is "<< fd<<"events is "<<events;
                return st(EPollFileObserver)::OnEventRemoveObserver;
            }
        }

        if(fd == serverfd) {
            struct sockaddr_in client_address;
            socklen_t client_addrLength = sizeof(struct sockaddr_in);
            //may be this is udp wangsl
            if(s!= nullptr && s->getType() == st(Socket)::Udp) {
                //ByteArray buff = createByteArray(st(Socket)::DefaultBufferSize);
                Socket newClient = nullptr;
                byte buff[st(Socket)::DefaultBufferSize];
                while(1) {
                    int length = recvfrom(fd, buff,st(Socket)::DefaultBufferSize, 0, (sockaddr*)&client_address, &client_addrLength);
                    if(newClient == nullptr) {
                        newClient = createSocket(createFileDescriptor(fd));
                        newClient->setType(st(Socket)::Udp);
                        newClient->setInetAddress(createInetAddress(
                                            createString(inet_ntoa(client_address.sin_addr)),
                                            ntohs(client_address.sin_port)));
                    }

                    monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(
                                                        st(SocketListener)::Message,
                                                        newClient,
                                                        createByteArray((const byte *)buff,length)));
                    monitor->mCondition->notify();
                    if(length != st(Socket)::DefaultBufferSize) {
                        break;
                    }
                }
                return st(EPollFileObserver)::OnEventOK;
            } else {
                int clientfd = accept(fd,( struct sockaddr* )&client_address, &client_addrLength );
                if(clientfd != -1) {
                    Socket s = createSocket(createFileDescriptor(clientfd));
                    s->setInetAddress(createInetAddress(
                                        createString(inet_ntoa(client_address.sin_addr)),
                                        ntohs(client_address.sin_port)));
                    {
                        monitor->addNewSocket(s,listener);
                        {
                            AutoLock l(monitor->mMutex);
                            monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(SocketListener)::Connect,s));
                            monitor->mCondition->notify();
                        }
                        monitor->bind(s->getFileDescriptor()->getFd(),listener,false);
                    }
                    return st(EPollFileObserver)::OnEventOK;
                }
            }
        }

        if((events & EPOLLIN) != 0) {
            {   
                while(1) {
                    byte buff[st(Socket)::DefaultBufferSize];
                    int length = read(fd, buff,st(Socket)::DefaultBufferSize);
                    if(length > 0) {
                        ByteArray data = createByteArray((const byte *)buff,length);
                        AutoLock l(monitor->mMutex);
                        monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(SocketListener)::Message,s,data));
                        monitor->mCondition->notify();
                    }

                    if(length != st(Socket)::DefaultBufferSize) {
                        break;
                    }
                }
            }
        }

        if((events & (EPOLLRDHUP|EPOLLHUP))!= 0) {
            {
                AutoLock l(monitor->mMutex);
                monitor->mThreadPublicTasks->putLast(createSocketMonitorTask(st(SocketListener)::Disconnect,s));
                monitor->mCondition->notify();
                return st(EPollFileObserver)::OnEventRemoveObserver;
            }
        }
        
        return st(EPollFileObserver)::OnEventOK;
        
    },l,serversocket,AutoClone(this));

    return 0;
}


void _SocketMonitor::close() {
    mPoll->close();
    isStop = 0;
    {
        AutoLock l(mMutex);
        mThreadLocalTasks->foreach([](LinkedList<SocketMonitorTask> &list){
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

_SocketMonitor::~_SocketMonitor() {
    delete []mCurrentSockets;
}

}