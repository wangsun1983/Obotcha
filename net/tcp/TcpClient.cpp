#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <stddef.h>

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "TcpClient.hpp"
#include "InitializeException.hpp"
#include "System.hpp"
#include "ByteArray.hpp"
#include "Error.hpp"

namespace obotcha {

_TcpClient::_TcpClient(String ip,int port,SocketListener l,int buff_size) {
    mServerIp = ip;
    mServerPort = port;

    serverAddr.sin_family = AF_INET;
    if(port > 0) {
        serverAddr.sin_port = htons(port);
    } else {
        throw InitializeException(createString("error tcp client porte"));
    }
    
    if(ip != nullptr) {
        serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    } else {
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
  
    mBufferSize = buff_size;
    int fd = TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_STREAM, 0));
    mSock = createSocket(fd);

    mListener = l;
    mSendTimeout = -1;
    mRcvTimeout = -1;
}

_TcpClient::_TcpClient(int port,SocketListener l,int buff_size):_TcpClient(nullptr,port,l,buff_size) {

}

void _TcpClient::setSendTimeout(long timeout) {
    mSendTimeout = timeout;
}

long _TcpClient::getSendTimeout() {
    return mSendTimeout;
}

void _TcpClient::setRcvTimeout(long timeout) {
    mRcvTimeout = timeout;
}

long _TcpClient::getRcvTimeout() {
    return mRcvTimeout;
}

int _TcpClient::onEvent(int fd,uint32_t events,ByteArray data) {
    if((events & EPOLLHUP)!= 0) {
        mListener->onDisconnect(createSocketResponser(fd));
        this->release();
    } else if((events & EPOLLIN) != 0) {
        mListener->onDataReceived(createSocketResponser(fd),data);
    }

    return st(EPollFileObserver)::OnEventOK;
}

int _TcpClient::getSock() {
    return mSock->getFd();
}
    
int _TcpClient::doConnect() {
    if(mRcvTimeout != -1) {
        struct timeval tv = {
            .tv_sec = mRcvTimeout/1000,
            .tv_usec = (mRcvTimeout%1000)*1000,
        };
        setsockopt(mSock->getFd(), SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    }

    if(mSendTimeout != -1) {
        struct timeval tv = {
            .tv_sec = mSendTimeout/1000,
            .tv_usec = (mSendTimeout%1000)*1000,
        };
        setsockopt(mSock->getFd(), SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    }

    if(TEMP_FAILURE_RETRY(connect(mSock->getFd(), (struct sockaddr *)&serverAddr, sizeof(serverAddr))) < 0) {
        close(mSock->getFd());
        return -1;
    }

    if(mListener != nullptr) {
        mListener->onConnect(createSocketResponser(mSock->getFd(),mServerIp,mServerPort));
    }

    struct sockaddr_in local_address;
    memset(&local_address,0,sizeof(struct sockaddr_in));

    socklen_t length = 0;
    int ret = getpeername(mSock->getFd(), ( struct sockaddr* )&local_address, &length);
    
    while(ntohs(local_address.sin_port ) == 0) {
        st(Thread)::msleep(30);
        memset(&local_address,0,sizeof(struct sockaddr_in));
        getpeername(mSock->getFd(), ( struct sockaddr* )&local_address, &length);
    }
    
    if(mListener != nullptr) {
        mEpollObserver = createEPollFileObserver();
        mEpollObserver->addObserver(mSock->getFd(),EPOLLIN|EPOLLHUP,AutoClone(this));
        mEpollObserver->start();
    } else {
        mEpollObserver = nullptr;
    }

    return ret;
}

int _TcpClient::doSend(ByteArray data) {
    return mSock->send(data);
}

int _TcpClient::doSend(ByteArray data,int size) {
    return mSock->send(data,size);
}

ByteArray _TcpClient::doReceive() {
    ByteArray data = createByteArray(mBufferSize);
    int len = read(mSock->getFd(),data->toValue(),mBufferSize);
    data->quickShrink(len);
    return data;
}

int _TcpClient::getBuffSize() {
    return mBufferSize;
}

void _TcpClient::release() {
    if(mSock != nullptr) {
        close(mSock->getFd());
        mSock = nullptr;
    }

    if(mEpollObserver != nullptr) {
        mEpollObserver->release();
        mEpollObserver = nullptr;
    }
}

_TcpClient::~_TcpClient() {
    release();
}

}

