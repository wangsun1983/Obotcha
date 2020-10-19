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
#include "Error.hpp"
#include "Byte.hpp"


namespace obotcha {

int _UdpServer::onEvent(int fd,uint32_t events,ByteArray pack) {
    if(pack != nullptr) {
        mListener->onDataReceived(createSocketResponser(fd),pack);
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
        return -NetBindFail;
    }
    
    if(mListener != nullptr) {
        mEpollObserver = createEPollFileObserver();
        mEpollObserver->addObserver(sock,EPOLLIN|EPOLLRDHUP,AutoClone(this));
        mEpollObserver->start();
    } else {
        mEpollObserver = nullptr;
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
        mEpollObserver = nullptr;
    }
}

_UdpServer::~_UdpServer() {
    release();
}

}