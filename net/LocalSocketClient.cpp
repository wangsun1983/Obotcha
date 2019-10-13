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

_LocalSocketClient::_LocalSocketClient(String domain,int recv_time,int buff_size) {

    mDomain = domain;
    
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars()); 

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
    
    mSock = socket(AF_UNIX, SOCK_STREAM, 0);
    //printf("create mSock is %d \n",mSock);
    mBuff = (char *)malloc(buff_size);
    mConnectMutex = createMutex("ConncetMutex");
}

int _LocalSocketClient::getSock() {
    return mSock;
}
    
int _LocalSocketClient::doConnect() {
    if(mSock < 0) {
        return -1;
    }

    //AutoMutex ll(mConnectMutex);

    int flags  = fcntl(mSock,F_GETFL,0);                          //获取文件的flags值。
    int setResult = fcntl(mSock,F_SETFL,flags &~O_NONBLOCK);    //设置成阻塞模式；
    //printf("setResult = %d",setResult);

    int ret = connect(mSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    //printf("connect ret is %d,mSock is %d \n",ret,mSock);
    if( ret < 0) {
        printf("connect fail,reason is %s \n",strerror(errno));
        return -1;
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

    ////printf( "local with ip: %s and port: %d\n",
    //inet_ntop( AF_INET, &local_address.sin_addr, local, INET_ADDRSTRLEN ), ntohs( local_address.sin_port ) );
    
    return 0;
}

int _LocalSocketClient::doSend(ByteArray data) {
    if(data == nullptr || data->size() == 0) {
        return  0;
    }
    
    return st(NetUtils)::sendTcpPacket(mSock,data);
}

ByteArray _LocalSocketClient::doReceive() {
    int len = recv(mSock, mBuff, mBufferSize, 0);
    //printf("tcp client len is %d \n",len);
    if(len <= 0) {
        printf("receive faild , error = %s \n", strerror(errno));
        return nullptr;
    }
    
    ByteArray data = createByteArray(mBuff,len);
    return data;
}

int _LocalSocketClient::getBuffSize() {
    return mBufferSize;
}

void _LocalSocketClient::release() {
    //AutoMutex ll(mConnectMutex);
    //printf("tcpclient release2\n");
    if(mSock >= 0) {
        close(mSock);
        mSock = -1;
    }

    if(mBuff != nullptr) {
        free(mBuff);
        mBuff = nullptr;
    }
}

_LocalSocketClient::~_LocalSocketClient() {
    release();
}

}

