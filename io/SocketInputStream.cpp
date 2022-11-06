#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <memory.h>
#include <netinet/in.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "Socket.hpp"
#include "SocketInputStream.hpp"

namespace obotcha {

_SocketInputStream::_SocketInputStream(sp<_Socket> s):_SocketInputStream(s->mSockImpl) { 
}

_SocketInputStream::_SocketInputStream(SocketImpl impl) {
    mImpl = impl;
}

long _SocketInputStream::read(ByteArray buffer) {
    return mImpl->read(buffer);
}

long _SocketInputStream::read(ByteArray buffer, int start) {
    return mImpl->read(buffer,start);
}

long _SocketInputStream::read(ByteArray buffer,int start,int length) {
    return mImpl->read(buffer,start,length);
}

void _SocketInputStream::close() { 
    mImpl = nullptr; 
}

_SocketInputStream::~_SocketInputStream() {
    mImpl = nullptr;
}

sp<_Socket> _SocketInputStream::recvDatagram(ByteArray buff) {
    return mImpl->recvDatagram(buff);
}

} // namespace obotcha
