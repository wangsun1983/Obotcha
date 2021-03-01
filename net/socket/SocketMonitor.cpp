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
        printf("monitor on event,fd is %d,s fd is %d \n",fd,sockfd);
        if(fd == sockfd) {
            listener->onConnect(createSocketResponser(fd));
        }else if((events & EPOLLHUP)!= 0) {
            listener->onDisconnect(createSocketResponser(fd));
        } else if((events & EPOLLIN) != 0) {
            listener->onDataReceived(createSocketResponser(fd),data);
        }
        
        return st(EPollFileObserver)::OnEventOK;
    },l,fd);
    
    return -1;
}


void _SocketMonitor::release() {
    mPoll->release();
}

int _SocketMonitor::remove(int fd) {
    return mPoll->removeObserver(fd);
}

}