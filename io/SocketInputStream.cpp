#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <stddef.h>
#include <unistd.h>


#include "SocketInputStream.hpp"
#include "Socket.hpp"

namespace obotcha {

_SocketInputStream::_SocketInputStream(sp<_Socket> s) {
    mSocket = s;
}

long _SocketInputStream::read(ByteArray buffer) {
    return ::read(mSocket->getFd(),buffer->toValue(),buffer->size());
}

void _SocketInputStream::close() {
    //TODO
}

_SocketInputStream::~_SocketInputStream() {

}

}
