#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "SocketOutputStream.hpp"
#include "Socket.hpp"

namespace obotcha {

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s) {
    mSocket = s;
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
        return -1;
    }

    while(1) {
        int result = ::write(mSocket->getFd(),sendData,size);
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