#include "SocketMonitor.hpp"

namespace obotcha {

_SocketMonitor::_SocketMonitor() {
    mPoll = createEPollFileObserver();
    mPoll->start();
}

int _SocketMonitor::bind(Socket s,SocketListener l) {
    bind(s->getFd(),l);
}

int _SocketMonitor::bind(ServerSocket s,SocketListener l) {
    bind(s->getFd(),l);
}

int _SocketMonitor::bind(int fd,SocketListener l) {
    printf("socket fd is %d \n",fd);
    mPoll->addObserver(fd,
                        EPOLLIN|EPOLLRDHUP|EPOLLHUP,
                        [](int fd,uint32_t events,ByteArray data,SocketListener &listener,int sockfd) {
        printf("monitor on event,fd is %d,s fd is %d,event is %x \n",fd,sockfd,events);
        if(fd == sockfd) {
            struct sockaddr_in client_address;
            socklen_t client_addrLength = sizeof(struct sockaddr_in);
            int clientfd = accept(fd,( struct sockaddr* )&client_address, &client_addrLength );
            printf("clientfd is %d \n",clientfd);
            if(clientfd != -1) {
                listener->onConnect(createSocketResponser(clientfd));
                return st(EPollFileObserver)::OnEventOK;
            }
        }
        
        if((events & (EPOLLHUP|EPOLLRDHUP))!= 0) {
            listener->onDisconnect(createSocketResponser(fd));
        } else if((events & EPOLLIN) != 0) {
            listener->onDataReceived(createSocketResponser(fd),data);
        } 
        
    },l,fd);
    
    return -1;
}


void _SocketMonitor::release() {
    printf("socketmonitor release \n");
    mPoll->release();
}

int _SocketMonitor::remove(int fd) {
    printf("_SocketMonitor remove fd \n");
    return mPoll->removeObserver(fd);
}

}