#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>  
#include <arpa/inet.h>

#include "SocketOutputStream.hpp"
#include "Socket.hpp"
#include "InetAddress.hpp"

namespace obotcha {

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s) {
    mSocket = s;
    if(mSocket->getType() == st(Socket)::Udp) {
        server_addr.sin_family = AF_INET;
        InetAddress addr = s->getInetAddress();
        server_addr.sin_port = htons(addr->getPort());          
        server_addr.sin_addr.s_addr = inet_addr(addr->getAddress()->toChars());
    }
}

long _SocketOutputStream::write(char c) {
    ByteArray data = createByteArray(1);
    data[0] = c;
    return write(data,1);
}

long _SocketOutputStream::write(ByteArray data) {
    return write(data,data->size());
}

long _SocketOutputStream::write(ByteArray data,long size) {
    byte *sendData = data->toValue();
    if(mSocket == nullptr || mSocket->isClosed()) {
        printf("socketoutput write fail \n");
        return -1;
    }

    while(1) {
        int result = -1;
        printf("mSocket type is %d \n",mSocket->getType());
        switch(mSocket->getType()) {
            case st(Socket)::Udp:
                printf("send udp \n");
                result = ::sendto(mSocket->getFd(), data->toValue(), data->size(), 0, (struct sockaddr *)&server_addr, sizeof(sockaddr_in));
            break;

            default:
                printf("send tcp,fd is %d,sendData is %s,size is %d \n",mSocket->getFd(),data->toString()->toChars(),size);
                result = ::write(mSocket->getFd(),sendData,size);
            break;
        }
        
        printf("socketoutput write result is %d,errno is %s \n",result,strerror(errno));
        if(result < 0) {
            if(errno == EAGAIN) {
                usleep(1000*10);
                continue;
            }
        } else if(result < size) {
            size -= result;
            sendData += result;
            usleep(1000*10);
            continue;
        }
        return result;
    }
}

void _SocketOutputStream::close() {
    mSocket = nullptr;
}

void _SocketOutputStream::flush() {
    //TODO
}


}