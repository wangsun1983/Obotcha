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

namespace obotcha {

_TcpClient::_TcpClient(String ip,int port,int recv_time,SocketListener l,int buff_size) {
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
    mSock = TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_STREAM, 0));
    mConnectMutex = createMutex("ConncetMutex");
    
    mListener = l;
}

_TcpClient::_TcpClient(int port,int recv_time,SocketListener l,int buff_size):_TcpClient(nullptr,port,recv_time,l,buff_size) {

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
    return mSock;
}
    
int _TcpClient::doConnect() {
    if(TEMP_FAILURE_RETRY(connect(mSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) < 0) {
        close(mSock);
        mSock = -1;
        return -1;
    }

    if(mListener != nullptr) {
        mListener->onConnect(createSocketResponser(mSock,mServerIp,mServerPort));
    }

    struct sockaddr_in local_address;
    memset(&local_address,0,sizeof(struct sockaddr_in));

    socklen_t length = 0;
    int ret = getpeername(mSock, ( struct sockaddr* )&local_address, &length);
    
    while(ntohs(local_address.sin_port ) == 0) {
        st(Thread)::msleep(30);
        memset(&local_address,0,sizeof(struct sockaddr_in));
        getpeername(mSock, ( struct sockaddr* )&local_address, &length);
    }
    
    if(mListener != nullptr) {
        mEpollObserver = createEPollFileObserver();
        mEpollObserver->addObserver(mSock,EPOLLIN|EPOLLHUP,AutoClone(this));
        mEpollObserver->start();
    } else {
        mEpollObserver = nullptr;
    }

    return ret;
}

int _TcpClient::doSend(ByteArray data) {
    if(data == nullptr || data->size() == 0||mSock == -1) {
        return  0;
    }

    return send(mSock,data->toValue(),data->size(),0);
}

ByteArray _TcpClient::doReceive() {
    ByteArray data = createByteArray(mBufferSize);
    int len = read(mSock,data->toValue(),mBufferSize);
    data->quickShrink(len);
    return data;
}

int _TcpClient::getBuffSize() {
    return mBufferSize;
}

void _TcpClient::release() {
    if(mSock >= 0) {
        close(mSock);
        mSock = -1;
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

