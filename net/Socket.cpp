#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Socket.hpp"

namespace obotcha {

_Socket::_Socket(int fd) {
    mFd = fd;
}

int _Socket::send(ByteArray data,int size) {
    byte *sendData = data->toValue();
    while(1) {
        int result = write(mFd,sendData,size);
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

int _Socket::send(ByteArray data) {
    this->send(data,data->size());
}

int _Socket::getFd() {
    return this->mFd;
}

}
