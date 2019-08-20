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

namespace obotcha {

_TcpClient::_TcpClient(String ip,int port,int recv_time,int buff_size) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    std::cout << "Connect Server: " << ip->toChars() << " : " << port << endl;
    mReceiveTimeout = recv_time;
    mBufferSize = buff_size;
    mSock = socket(AF_INET, SOCK_STREAM, 0);
}
    
int _TcpClient::doConnect() {
    if(mSock < 0) {
        return -1;
    }

    if(connect(mSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("connect fail,reason is %s \n",strerror(errno));
        return -1;
    }

    return 0;
}

int _TcpClient::doSend(ByteArray data) {
    return st(NetUtils)::sendTcpPacket(mSock,data);
}

ByteArray _TcpClient::doReceive() {
    ByteArray data = createByteArray(mBufferSize);
    recv(mSock, data->toValue(), mBufferSize, 0);
    return data;
}

int _TcpClient::getBuffSize() {
    return mBufferSize;
}

void _TcpClient::release() {
    close(mSock);
}

_TcpClient::~_TcpClient() {
    close(mSock);
}

}

