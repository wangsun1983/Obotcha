/**
 * @file SocketInputStream.cpp
 * @brief SocketInputStream is meant for reading memory-mapped file of raw bytes 
 *        from socket.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */
#include "Socket.hpp"
#include "SocketInputStream.hpp"
#include "Inspect.hpp"

namespace obotcha {

_SocketInputStream::_SocketInputStream(sp<_Socket> s):_SocketInputStream(s->mSockImpl) { 
}

_SocketInputStream::_SocketInputStream(SocketImpl impl):mImpl(impl) {
}

long _SocketInputStream::read(ByteArray buffer) {
    Inspect(mImpl == nullptr,-1)
    return mImpl->read(buffer);
}

long _SocketInputStream::read(ByteArray buffer, uint64_t start) {
    Inspect(mImpl == nullptr,-1)
    return mImpl->read(buffer,start);
}

long _SocketInputStream::read(ByteArray buffer,uint64_t start,uint64_t length) {
    Inspect(mImpl == nullptr,-1)
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
