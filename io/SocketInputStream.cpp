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

_SocketInputStream::_SocketInputStream(sp<_Socket> s) { mSocket = s; }

long _SocketInputStream::read(ByteArray buffer) {
    return ::read(mSocket->getFileDescriptor()->getFd(), buffer->toValue(),
                  buffer->size());
}

long _SocketInputStream::read(ByteArray buffer, int start) {
    return ::read(mSocket->getFileDescriptor()->getFd(),
                  &buffer->toValue()[start], buffer->size() - start);
}

void _SocketInputStream::close() { mSocket = nullptr; }

_SocketInputStream::~_SocketInputStream() {}

} // namespace obotcha
