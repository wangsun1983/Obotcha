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

namespace obotcha {

_UdpClient::_UdpClient(int port,SocketListener l):_UdpClient(nullptr,port,l) {

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
        mObserver->addObserver(sock,EPOLLIN|EPOLLHUP,AutoClone(this));
        mObserver->start();
    } else {
        mObserver = nullptr;
    }
}

int _UdpClient::onEvent(int fd,uint32_t events,ByteArray pack) {
    if((events & EPOLLHUP) != 0) {
        listener->onDisconnect(createSocketResponser(fd));
    }
    
    if(pack != nullptr) {
        listener->onDataReceived(createSocketResponser(sock),pack);
    }
    return 0;
}

int _UdpClient::send(ByteArray data) {
    int server_len = sizeof(struct sockaddr_in);
    return sendto(sock, data->toValue(), data->size(), 0, (struct sockaddr *)&serverAddr, server_len);
}

_UdpClient::~_UdpClient() {
    release();
}

void _UdpClient::start() {
    //Nothing
}

void _UdpClient::release() {

    if(sock != -1) {
        close(sock);
        sock = -1;
    }
    
    if(mObserver != nullptr) {
        mObserver->release();
        mObserver = nullptr;
    }
}

}