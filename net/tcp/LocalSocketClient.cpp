#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <stddef.h>

#include "System.hpp"
#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "LocalSocketClient.hpp"
#include "InitializeException.hpp"

namespace obotcha {

int _LocalSocketClient::onEvent(int fd,uint32_t events,ByteArray data) {
    if((events & EPOLLHUP)!= 0) {
        mSocketListener->onDisconnect(createSocketResponser(fd));
    } else if((events & EPOLLIN) != 0) {
        mSocketListener->onDataReceived(createSocketResponser(fd),data);
    }

    return st(EPollFileObserver)::OnEventOK;
}

_LocalSocketClient::_LocalSocketClient(String domain,int recv_time,int buff_size,SocketListener l) {

    mDomain = domain;
    
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars()); 

    mReceiveTimeout = recv_time;
    mBufferSize = buff_size;
    mSock = TEMP_FAILURE_RETRY(socket(AF_UNIX, SOCK_STREAM, 0));
    
    mSocketListener = l;
}

int _LocalSocketClient::getSock() {
    return mSock;
}
    
int _LocalSocketClient::doConnect() {
    if(mSock < 0) {
        return -1;
    }

    if(connect(mSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        return -1;
    }

    if(mSocketListener != nullptr) {
        mSocketListener->onConnect(createSocketResponser(mDomain,mSock));
    }

    struct sockaddr_in local_address;
    memset(&local_address,0,sizeof(struct sockaddr_in));

    socklen_t length = 0;
    int ret = getpeername(mSock, ( struct sockaddr* )&local_address, &length);
    
    while(ntohs( local_address.sin_port ) == 0) {
        st(Thread)::msleep(30);
        memset(&local_address,0,sizeof(struct sockaddr_in));
        getpeername(mSock, ( struct sockaddr* )&local_address, &length);
    }

    if(mSocketListener != nullptr) {
        mObserver = createEPollFileObserver();
        mObserver->addObserver(mSock,EPOLLIN|EPOLLHUP,AutoClone(this));
        mObserver->start();
    }

    return ret;
}

int _LocalSocketClient::doSend(ByteArray data) {
    if(data == nullptr || data->size() == 0) {
        return  0;
    }
    return send(mSock,data->toValue(),data->size(),0);
}


ByteArray _LocalSocketClient::doReceive() {
    ByteArray buff = createByteArray(mBufferSize);
    int len = read(mSock,buff->toValue(),mBufferSize);
    buff->quickShrink(len);
    return buff;
}

void _LocalSocketClient::release() {
    if(mSock >= 0) {
        close(mSock);
        mSock = -1;
    }

    if(mObserver != nullptr) {
        this->mObserver->release();
    }
}

_LocalSocketClient::~_LocalSocketClient() {
    release();
}

}

