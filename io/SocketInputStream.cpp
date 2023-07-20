#include "Socket.hpp"
#include "SocketInputStream.hpp"
#include "Inspect.hpp"

namespace obotcha {

_SocketInputStream::_SocketInputStream(sp<_Socket> s):_SocketInputStream(s->mSockImpl) { 
}

_SocketInputStream::_SocketInputStream(SocketImpl impl):mImpl(impl) {
}

long _SocketInputStream::read(ByteArray buffer) {
    Inspect(mImpl == nullptr,-1);
    return mImpl->read(buffer);
}

long _SocketInputStream::read(ByteArray buffer, int start) {
    Inspect(mImpl == nullptr,-1);
    return mImpl->read(buffer,start);
}

long _SocketInputStream::read(ByteArray buffer,int start,int length) {
    Inspect(mImpl == nullptr,-1);
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
