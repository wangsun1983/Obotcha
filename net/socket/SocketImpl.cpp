#include "SocketImpl.hpp"
#include "Socket.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_SocketImpl::_SocketImpl() {
    _init();
}

_SocketImpl::_SocketImpl(FileDescriptor fd) {
    _init();
    sock = fd;
}

_SocketImpl::_SocketImpl(InetAddress address, SocketOption option) {
    _init();
    this->address = address;
    this->option = option;
    if(option != nullptr) {
        mBuffSize = option->getRcvBuffSize();
    }
}

void _SocketImpl::_init() {
    sock = nullptr;
    address = nullptr;
    option = nullptr;
    mBuffSize = st(SocketOption)::DefaultRecvBuffSize;
}

int _SocketImpl::close() {
    return sock->close();
}

FileDescriptor _SocketImpl::getFileDescriptor() {
    return sock;
}

InetAddress _SocketImpl::getInetAddress() {
    return address;
}

int _SocketImpl::write(ByteArray data,int start,int length) {
    int size = (length == -1?data->size() - start:length);
    if(size > data->size()) {
        Trigger(IllegalArgumentException,"oversize");
    }

    return ::write(sock->getFd(),data->toValue() + start,size);
}

int _SocketImpl::read(ByteArray data,int start,int length) {
    int size = (length == -1?data->size() - start:length);
    int destLength = ((start + size) > data->size())?(data->size() - start):size;

    return ::read(sock->getFd(),data->toValue() + start,destLength);
}

ByteArray _SocketImpl::read() {
    ByteArray buff = createByteArray(mBuffSize);
    int length = ::read(sock->getFd(), buff->toValue(), mBuffSize);
    buff->quickShrink(length);
    return buff;
}

} // namespace obotcha
