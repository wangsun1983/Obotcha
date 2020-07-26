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
#include "TcpClient.hpp"
#include "NetUtils.hpp"
#include "InitializeException.hpp"

namespace obotcha {

//TcpClient-------------
_TcpClient::_TcpClient(String ip,int port,int recv_time,SocketListener l,int buff_size) {
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
  
    if(buff_size >0) {
        mBufferSize = buff_size;
    } else {
        throw InitializeException(createString("error tcp client buff size"));
    }

    mSock = socket(AF_INET, SOCK_STREAM, 0);
    mBuff = (byte *)malloc(buff_size);
    mConnectMutex = createMutex("ConncetMutex");
    
    mListener = l;
}

_TcpClient::_TcpClient(int port,int recv_time,SocketListener l,int buff_size):_TcpClient{nullptr,port,recv_time,l,buff_size} {

}

int _TcpClient::onEvent(int fd,uint32_t events,ByteArray data) {
    if((events & EPOLLHUP)!= 0) {
        mListener->onDisconnect(fd);
        this->release();
    } else if((events & EPOLLIN) != 0) {
        mListener->onAccept(fd,nullptr,-1,data);
    }

    return st(EPollFileObserver)::OnEventOK;
}

int _TcpClient::getSock() {
    return mSock;
}
    
int _TcpClient::doConnect() {
    //AutoMutex ll(mConnectMutex);
    int ret = connect(mSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if( ret < 0) {
        close(mSock);
        mSock = -1;
        return -1;
    }

    struct sockaddr_in local_address;
    memset(&local_address,0,sizeof(struct sockaddr_in));

    socklen_t length = 0;
    ret = getpeername(mSock, ( struct sockaddr* )&local_address, &length);

    while(ntohs( local_address.sin_port ) == 0) {
        st(Thread)::msleep(30);
        memset(&local_address,0,sizeof(struct sockaddr_in));
        ret = getpeername(mSock, ( struct sockaddr* )&local_address, &length);
    }

    //create epoll observer?
    if(mListener != nullptr) {
        TcpClient v;
        v.set_pointer(this);
        
        EPollFileObserverListener l;
        l.set_pointer(this);
        mEpollObserver = createEPollFileObserver();
        mEpollObserver->addObserver(mSock,EPOLLIN|EPOLLHUP,l);
        mEpollObserver->start();
    }

    return ret;
}

int _TcpClient::doSend(ByteArray data) {
    if(data == nullptr || data->size() == 0||mSock == -1) {
        return  0;
    }
    return st(NetUtils)::sendTcpPacket(mSock,data);
}

ByteArray _TcpClient::doReceive() {
    //static int recvsize = 1024*4;
    byte buff[mBufferSize];
    int len = read(mSock,buff,mBufferSize);
    ByteArray data = createByteArray((const byte *)buff,len);
    //while(len == recvsize) {
    //   len =  read(mSock,buff,recvsize);
    //   data->append(buff,len);
    //}

    return data;
}

int _TcpClient::getBuffSize() {
    return mBufferSize;
}

void _TcpClient::release() {
    //AutoMutex ll(mConnectMutex);
    if(mSock >= 0) {
        close(mSock);
        mSock = -1;
    }

    if(mBuff == nullptr) {
        free(mBuff);
        mBuff = nullptr;
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

