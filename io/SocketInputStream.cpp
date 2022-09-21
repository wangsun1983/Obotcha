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

_SocketInputStream::_SocketInputStream(sp<_Socket> s):_SocketInputStream(s->getSockImpl()) { 
}

_SocketInputStream::_SocketInputStream(SocketImpl sockimpl) {
    impl = sockimpl;
}

long _SocketInputStream::read(ByteArray buffer) {
    return impl->read(buffer);
}

long _SocketInputStream::read(ByteArray buffer, int start) {
    return impl->read(buffer,start);
}

long _SocketInputStream::read(ByteArray buffer,int start,int length) {
    return impl->read(buffer,start,length);
}

void _SocketInputStream::close() { 
    impl = nullptr; 
}

_SocketInputStream::~_SocketInputStream() {
    impl = nullptr;
}

} // namespace obotcha
