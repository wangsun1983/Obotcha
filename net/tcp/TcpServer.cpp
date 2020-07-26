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

#include "AutoLock.hpp"
#include "TcpServer.hpp"
#include "Pipe.hpp"
#include "NetUtils.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "Enviroment.hpp"


namespace obotcha {

_TcpServer::_TcpServer(String ip,int port):_TcpServer{ip,port,nullptr} {

}

_TcpServer::_TcpServer(int port,SocketListener l):_TcpServer{nullptr,port,l} {
    
}

_TcpServer::_TcpServer(String ip,int port,SocketListener l,int connectnum) {

    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(port);
    if(ip != nullptr) {
        serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    } else {
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    mConnectionNum = connectnum;

    while(1) {
        mListener = l;
        
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if(sock < 0) {
            break;
        }
        
        return;
    }
    
    throw InitializeException("tcp initialize");
}

int _TcpServer::connect() {
    int opt = 1;
    
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
        return -AttributeSetFail;
    }

    if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        return -NetBindFail;
    }

    int ret = listen(sock, mConnectionNum);
    if(ret < 0) {
        return -NetListenFail;
    }

    if(mListener != nullptr) {
        mObserver = createEPollFileObserver();
        //mLocalListener = createLocalTcpSocketObserver(mListener,sock,mObserver);
        EPollFileObserverListener listener;
        listener.set_pointer(this);
        mObserver->addObserver(sock,EPOLLIN|EPOLLRDHUP,listener);
    }

    return 0;
}

int _TcpServer::onEvent(int fd,uint32_t events,ByteArray pack) {
    if(fd == sock) {
        struct sockaddr_in client_address;
        socklen_t client_addrLength = sizeof(struct sockaddr_in);
        int clientfd = accept(fd,( struct sockaddr* )&client_address, &client_addrLength );
        if(clientfd == -1) {
            printf("accept fail,error is %s \n",strerror(errno));
            return 0;
        }

        mListener->onConnect(clientfd,
                            createString(inet_ntoa(client_address.sin_addr)),
                            ntohs(client_address.sin_port));
        
        EPollFileObserverListener v;
        v.set_pointer(this);
        //printf("add observer by socket!!!! ,clientfd is %d\n",clientfd);
        mObserver->addObserver(clientfd,EPOLLIN|EPOLLRDHUP,v);
    } else {
        if((events & EPOLLRDHUP) != 0) {
            if(mListener != nullptr) {
                mListener->onDisconnect(fd);
            }
        }

        if(pack != nullptr && pack->size() != 0) {
            if(mListener != nullptr) {
                mListener->onAccept(fd,nullptr,-1,pack);
            }
        }

        
    }

    return  0;
}

int _TcpServer::start() {
    
    int result = connect();
    if(result != 0) {
        printf("connect fail,result is %d \n",result);
        return result;
    }

    return 0;
}

void _TcpServer::release() {
    mObserver->release();
    if(sock != -1) {
        close(sock);
        sock = -1;
    }
}

int _TcpServer::send(int fd,ByteArray data) {
    return st(NetUtils)::sendTcpPacket(fd,data);
}

_TcpServer::~_TcpServer() {
    release();
}

}