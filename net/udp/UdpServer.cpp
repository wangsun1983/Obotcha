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
#include <errno.h>

#include "AutoLock.hpp"
#include "UdpServer.hpp"
#include "Pipe.hpp"
#include "NetUtils.hpp"
#include "Error.hpp"
#include "Byte.hpp"

#define EPOLL_SIZE 1024*8

#define BUFF_SIZE 1024*64

namespace obotcha {

int _UdpServer::onEvent(int fd,uint32_t events,ByteArray pack) {
    byte recv_buf[BUFF_SIZE];
    printf("fd is %d,sock is %d \n",fd,sock);
    if(pack != nullptr) {
        mListener->onAccept(fd,nullptr,
                                    -1,
                                    pack);
    }
    
    return  0;
}

_UdpServer::_UdpServer(int port,SocketListener l):_UdpServer{nullptr,port,l} {

}

_UdpServer::_UdpServer(String ip,int port,SocketListener l) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if(ip == nullptr) {
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    mListener = l;
    
    mEpollObserver = nullptr;
}

int _UdpServer::connect() {
    int opt = SO_REUSEADDR;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    if( bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("bind sock failed,reson is %s \n",strerror(errno));
        return -NetBindFail;
    }
    printf("sock is %d \n",sock);
    
    if(mListener != nullptr) {
        mEpollObserver = createEPollFileObserver();
        EPollFileObserverListener listener;
        listener.set_pointer(this);
        mEpollObserver->addObserver(sock,EPOLLIN|EPOLLRDHUP,listener);
        mEpollObserver->start();
    }

    return 0;
}

int _UdpServer::start() {
    
    int result = connect();
    if(result != 0) {
        return result;
    }

    return 0;
}

void _UdpServer::release() {
    
    if(sock != -1) {
        close(sock);
        sock = -1;
    }

    if(mEpollObserver != nullptr) {
        mEpollObserver->release();
    }
}

//int _UdpServer::send(String ip,int port,ByteArray data) {
//    return st(NetUtils)::sendUdpPacket(sock,ip,port,data);
//}

_UdpServer::~_UdpServer() {
    release();
}

}