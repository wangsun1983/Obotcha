#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <functional>

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

    if((fcntl(s->getFd(),F_GETFL) & O_NONBLOCK) != 0) {
        mChannel = createAsyncOutputChannel(s->getFd(),
                                            std::bind(&_SocketOutputStream::_write,this,std::placeholders::_1,std::placeholders::_2));
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
    if(data->size() > size) {
        data->quickShrink(size);
    }
    
    if(mChannel != nullptr) {
        mChannel->write(data);
        return size;
    }
    return _write(mSocket->getFd(),data);
}

long _SocketOutputStream::_write(int fd,ByteArray data) {
    byte *sendData = data->toValue();
    
    if(mSocket == nullptr || mSocket->isClosed()) {
        return -1;
    }

    switch(mSocket->getType()) {
        case st(Socket)::Udp:
            return ::sendto(mSocket->getFd(), data->toValue(), data->size(), 0, (struct sockaddr *)&server_addr, sizeof(sockaddr_in));
        break;

        default:
            return ::write(mSocket->getFd(),sendData,data->size());
        break;
    }

    return -1;
}

void _SocketOutputStream::close() {
    mSocket = nullptr;
    if(mChannel != nullptr) {
        mChannel->close();
    }

}

void _SocketOutputStream::flush() {
    //TODO
}


}