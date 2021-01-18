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
#include "Error.hpp"
#include "InitializeException.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"


namespace obotcha {

//-------------------TcpServer----------------------
_TcpServer::_TcpServer(String ip,int port):_TcpServer(ip,port,nullptr) {

}

_TcpServer::_TcpServer(int port,SocketListener l):_TcpServer(nullptr,port,l) {
    
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
    mListener = l;

    mSocketMapMutex = createMutex();
    mSocketMap = createHashMap<int,Socket>();

    mSendTimeout = -1;
    mRcvTimeout = -1;
}

void _TcpServer::setSendTimeout(long timeout) {
    mSendTimeout = timeout;
}

long _TcpServer::getSendTimeout() {
    return mSendTimeout;
}

void _TcpServer::setRcvTimeout(long timeout) {
    mRcvTimeout = timeout;
}

long _TcpServer::getRcvTimeout() {
    return mRcvTimeout;
}

int _TcpServer::connect() {
    int opt = 1;
    
    sock = TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_STREAM, 0));

    if(mRcvTimeout != -1) {
        struct timeval tv = {
            .tv_sec = mRcvTimeout/1000,
            .tv_usec = (mRcvTimeout%1000)*1000,
        };
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    }

    if(mSendTimeout != -1) {
        struct timeval tv = {
            .tv_sec = mSendTimeout/1000,
            .tv_usec = (mSendTimeout%1000)*1000,
        };
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    }

    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
        return -AttributeSetFail;
    }

    if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        return -NetBindFail;
    }

    if(listen(sock, mConnectionNum) < 0) {
        return -NetListenFail;
    }

    if(mListener != nullptr) {
        mObserver = createEPollFileObserver();
        mObserver->addObserver(sock,EPOLLIN|EPOLLRDHUP,AutoClone(this));
    } else {
        mObserver = nullptr;
    }

    return 0;
}

void _TcpServer::deMonitor(int fd) {
    mObserver->removeObserver(fd);
}

int _TcpServer::onEvent(int fd,uint32_t events,ByteArray pack) {
    if(fd == sock) {
        struct sockaddr_in client_address;
        socklen_t client_addrLength = sizeof(struct sockaddr_in);
        int clientfd = accept(fd,( struct sockaddr* )&client_address, &client_addrLength );
        if(clientfd == -1) {
            LOG(ERROR)<<"Accept fail,error is "<<strerror(errno);
            return st(EPollFileObserver)::OnEventOK;
        }

        if(mRcvTimeout != -1) {
            struct timeval tv = {
                .tv_sec = mRcvTimeout/1000,
                .tv_usec = (mRcvTimeout%1000)*1000,
            };
            setsockopt(clientfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
        }

        if(mSendTimeout != -1) {
            struct timeval tv = {
                .tv_sec = mSendTimeout/1000,
                .tv_usec = (mSendTimeout%1000)*1000,
            };
            setsockopt(clientfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
        }

        Socket tcpsock = createSocket(clientfd);
        {
            AutoLock l(mSocketMapMutex);
            mSocketMap->put(clientfd,tcpsock);
        }

        mObserver->addObserver(clientfd,EPOLLIN|EPOLLRDHUP,AutoClone(this));
        
        mListener->onConnect(createSocketResponser(clientfd,
                            createString(inet_ntoa(client_address.sin_addr)),
                            ntohs(client_address.sin_port)));
    } else {
        if(pack != nullptr && pack->size() != 0) {
            mListener->onDataReceived(createSocketResponser(fd),pack);
        }

        if((events & EPOLLRDHUP) != 0) {
            mListener->onDisconnect(createSocketResponser(fd));
            AutoLock l(mSocketMapMutex);
            mSocketMap->remove(fd);
        }
    }

    return st(EPollFileObserver)::OnEventOK;
}

int _TcpServer::start() {
    return connect();
}

void _TcpServer::release() {
    if(mObserver != nullptr) {
        mObserver->release();
        mObserver = nullptr;
    }

    if(sock != -1) {
        close(sock);
        sock = -1;
    }
}

_TcpServer::~_TcpServer() {
    release();
}

Socket _TcpServer::getSocket(int fd) {
    AutoLock l(mSocketMapMutex);
    return mSocketMap->get(fd);
}

}