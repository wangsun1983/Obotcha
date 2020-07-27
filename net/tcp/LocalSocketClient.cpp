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

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "LocalSocketClient.hpp"
#include "NetUtils.hpp"
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

    if(recv_time > 0) {
        mReceiveTimeout = recv_time;
    } else {
        throw InitializeException(createString("error tcp client recv time"));
    }
    
    if(buff_size >0) {
        mBufferSize = buff_size;
    } else {
        throw InitializeException(createString("error tcp client buff size"));
    }
    
    mSock = socket(AF_UNIX, SOCK_STREAM, 0);
    
    mSocketListener = l;
}

int _LocalSocketClient::getSock() {
    return mSock;
}
    
int _LocalSocketClient::doConnect() {
    if(mSock < 0) {
        return -1;
    }

    int ret = connect(mSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if( ret < 0) {
        return -1;
    }

    if(mSocketListener != nullptr) {
        mSocketListener->onConnect(createSocketResponser(mDomain,mSock));
    }

    struct sockaddr_in local_address;
    memset(&local_address,0,sizeof(struct sockaddr_in));

    socklen_t length = 0;
    ret = getpeername(mSock, ( struct sockaddr* )&local_address, &length);
    //char local[INET_ADDRSTRLEN ];
   
    while(ntohs( local_address.sin_port ) == 0) {
        st(Thread)::msleep(30);
        memset(&local_address,0,sizeof(struct sockaddr_in));
        ret = getpeername(mSock, ( struct sockaddr* )&local_address, &length);
    }

    //add to epoll fd
    if(mSocketListener != nullptr) {
        EPollFileObserverListener l;
        l.set_pointer(this);
        mObserver = createEPollFileObserver();
        mObserver->addObserver(mSock,EPOLLIN|EPOLLHUP,l);
        mObserver->start();
    }

    return ret;
}

int _LocalSocketClient::doSend(ByteArray data) {
    if(data == nullptr || data->size() == 0) {
        return  0;
    }
    
    return st(NetUtils)::sendTcpPacket(mSock,data);
}


ByteArray _LocalSocketClient::doReceive() {
    byte buff[mBufferSize];
    int len = read(mSock,buff,mBufferSize);
    ByteArray data = createByteArray((const byte *)buff,len);

    return data;
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

