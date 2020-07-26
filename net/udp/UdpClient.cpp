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

#include "UdpClient.hpp"
#include "NetUtils.hpp"

#define EPOLL_SIZE 128

#define BUF_SIZE 1024*64

namespace obotcha {

_UdpClient::_UdpClient(int port,SocketListener l):_UdpClient{nullptr,port,l} {

}

_UdpClient::_UdpClient(String ip,int port,SocketListener l) {

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if(ip != nullptr) {
        serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    } else {
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    listener = l;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(l != nullptr) {
        mObserver = createEPollFileObserver();
        EPollFileObserverListener ll;
        ll.set_pointer(this);
        mObserver->addObserver(sock,EPOLLIN|EPOLLHUP,ll);
        mObserver->start();
    }
}

int _UdpClient::onEvent(int fd,uint32_t events,ByteArray pack) {
    if((events & EPOLLHUP) != 0) {
        listener->onDisconnect(fd);
    }
    
    if(pack != nullptr) {
        listener->onAccept(sock,nullptr,-1,pack);
    }
}

bool _UdpClient::init() {
    //sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        return false;
    }
    
    return true;
}

int _UdpClient::send(ByteArray data) {
    //return st(NetUtils)::sendUdpPacket(sock,data);
    return st(NetUtils)::sendUdpPacket(sock,&serverAddr,data);
}

_UdpClient::~_UdpClient() {
    release();
}

void _UdpClient::start() {
    init();
}

void _UdpClient::release() {

    if(sock != -1) {
        close(sock);
        sock = -1;
    }
    
    if(mObserver != nullptr) {
        mObserver->release();
    }
}

}