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

_TcpClient::_TcpClient(int port,int recv_time,int buff_size) {

    serverAddr.sin_family = AF_INET;
    if(port > 0) {
        serverAddr.sin_port = htons(port);
    } else {
        throw createInitializeException(createString("error tcp client porte"));
    }

    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(recv_time > 0) {
        mReceiveTimeout = recv_time;
    } else {
        throw createInitializeException(createString("error tcp client recv time"));
    }
    
    if(buff_size >0) {
        mBufferSize = buff_size;
    } else {
        throw createInitializeException(createString("error tcp client buff size"));
    }
    
    mSock = socket(AF_INET, SOCK_STREAM, 0);
    //printf("create mSock is %d \n",mSock);
    mBuff = (char *)malloc(buff_size);
    mConnectMutex = createMutex("ConncetMutex");
}

_TcpClient::_TcpClient(String ip,int port,int recv_time,int buff_size) {
    serverAddr.sin_family = AF_INET;
    if(port > 0) {
        serverAddr.sin_port = htons(port);
    } else {
        throw createInitializeException(createString("error tcp client porte"));
    }

    serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());

    if(recv_time > 0) {
        mReceiveTimeout = recv_time;
    } else {
        throw createInitializeException(createString("error tcp client recv time"));
    }
    
    if(buff_size >0) {
        mBufferSize = buff_size;
    } else {
        throw createInitializeException(createString("error tcp client buff size"));
    }

    mSock = socket(AF_INET, SOCK_STREAM, 0);
    //printf("create mSock is %d \n",mSock);
    mBuff = (char *)malloc(buff_size);
    mConnectMutex = createMutex("ConncetMutex");
}

int _TcpClient::getSock() {
    return mSock;
}
    
int _TcpClient::doConnect() {
    if(mSock < 0) {
        return -1;
    }

    //AutoMutex ll(mConnectMutex);
    int ret = connect(mSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    //printf("connect ret is %d,mSock is %d \n",ret,mSock);
    if( ret < 0) {
        //printf("connect fail,reason is %s \n",strerror(errno));
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

    return ret;
}

int _TcpClient::doSend(ByteArray data) {
    if(data == nullptr || data->size() == 0) {
        return  0;
    }
    
    return st(NetUtils)::sendTcpPacket(mSock,data);
}

ByteArray _TcpClient::doReceive() {
    int len = recv(mSock, mBuff, mBufferSize, 0);
    //printf("tcp client len is %d \n",len);
    if(len == 0) {
        return nullptr;
    }
    
    ByteArray data = createByteArray(mBuff,len);
    return data;
}

int _TcpClient::getBuffSize() {
    return mBufferSize;
}

void _TcpClient::release() {
    //AutoMutex ll(mConnectMutex);
    //printf("tcpclient release2\n");
    if(mSock >= 0) {
        close(mSock);
    }

    if(mBuff == nullptr) {
        free(mBuff);
        mBuff = nullptr;
    }
}

_TcpClient::~_TcpClient() {
    release();
}

}

