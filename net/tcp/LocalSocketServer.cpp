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
#include "LocalSocketServer.hpp"
#include "Pipe.hpp"
#include "NetUtils.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_SysTcpSocketObserver::_SysTcpSocketObserver(SocketListener l,int sock,EPollFileObserver o) {
    mListener = l;
    mSock = sock;
    mObserver = o;
}

int _SysTcpSocketObserver::onEvent(int fd,uint32_t events,ByteArray pack) {
    if(fd == mSock) {
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
        
        SysTcpSocketObserver v;
        v.set_pointer(this);
        printf("add observer by socket!!!! ,clientfd is %d\n",clientfd);
        mObserver->addObserver(clientfd,EPOLLIN|EPOLLRDHUP,v);
    } else {
        if((events & EPOLLIN) != 0) {
            if(mListener != nullptr && pack != nullptr) {
                mListener->onAccept(fd,nullptr,-1,pack);
            }
        }

        if((events & EPOLLRDHUP) != 0) {
            if(mListener != nullptr) {
                mListener->onDisconnect(fd);
            }
        }
    }

    return  0;
}


int _LocalSocketServer::start() {
    int result = connect();
    if(result != 0) {
        printf("connect fail,result is %d \n",result);
        return result;
    }

    return 0;
}

int _LocalSocketServer::tryStart() {
    int result = tryConnect();
    if(result != 0) {
        printf("connect fail,result is %d \n",result);
        return result;
    }

    return 0;
}

int _LocalSocketServer::getSock() {
    return sock;
}

_LocalSocketServer::_LocalSocketServer(String domain,SocketListener l,int connectnum,int recvsize) {
    String reason;

    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars());  
    
    while(1) {
        mConectNum = connectnum;
        mListener = l;

        sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if(sock < 0) {
            reason = createString("Sock Create Fail");
            break;
        }
        mDomain = domain;
        return;
    }

    throw InitializeException(reason);
}

int _LocalSocketServer::tryConnect() {

    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);   

    if( bind(sock, (struct sockaddr *)&serverAddr, len) < 0) {
        if(errno == EADDRINUSE) {
            return -NetAddrAlreadyUseFail; 
        }

        return -NetBindFail;
    }

    int ret = listen(sock, mConectNum);
    if(ret < 0) {
        return -NetListenFail;
    }
    
    if(mListener != nullptr) {
        mEpollFileObserver = createEPollFileObserver();
        mSysTcpListener = createSysTcpSocketObserver(mListener,sock,mEpollFileObserver);
        mEpollFileObserver->addObserver(sock,EPOLLIN|EPOLLRDHUP,mSysTcpListener);
    }

    return 0;
}

int _LocalSocketServer::connect() {
    
    unlink(mDomain->toChars());

    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);   

    if( bind(sock, (struct sockaddr *)&serverAddr, len) < 0) {
        return -NetBindFail;
    }

    int ret = listen(sock, mConectNum);

    if(ret < 0) {
        return -NetListenFail;
    }
    
    if(mListener != nullptr) {
        mEpollFileObserver = createEPollFileObserver();
        mSysTcpListener = createSysTcpSocketObserver(mListener,sock,mEpollFileObserver);
        mEpollFileObserver->addObserver(sock,EPOLLIN|EPOLLRDHUP,mSysTcpListener);
    }

    return 0;
}

void _LocalSocketServer::release() {
    mEpollFileObserver->release();
    if(sock != -1) {
        close(sock);
        sock = -1;
    }
}

int _LocalSocketServer::send(int fd,ByteArray data) {
    return st(NetUtils)::sendTcpPacket(fd,data);
}

_LocalSocketServer::~_LocalSocketServer() {
    release();
}

}