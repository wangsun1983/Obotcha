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

_SocketMonitor::_SocketMonitor() {
    mServerSockFd = -1;
    mMutex = createMutex();
    mSocks = createHashMap<int,Socket>();

    mPoll = createEPollFileObserver();
    mPoll->start();
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
                        [](int fd,uint32_t events,ByteArray data,SocketListener &listener,int sockfd,Mutex mutex,HashMap<int,Socket> socks) {
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
                }

                listener->onConnect(s);
                return st(EPollFileObserver)::OnEventOK;
            }
        }

        Socket s = nullptr;
        {
            AutoLock l(mutex);
            s = socks->get(fd);
        }
        
        if((events & (EPOLLHUP|EPOLLRDHUP))!= 0) {
            listener->onDisconnect(s);
            {
                AutoLock l(mutex);
                socks->remove(fd);
            }
        } else if((events & EPOLLIN) != 0) {
            listener->onDataReceived(s,data);
        } 
        
    },l,mServerSockFd,mMutex,mSocks);
    
    return -1;
}


void _SocketMonitor::release() {
    mPoll->release();
}

int _SocketMonitor::remove(Socket s) {
    return mPoll->removeObserver(s->getFd());
}

}