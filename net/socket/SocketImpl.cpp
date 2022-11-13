#include "SocketImpl.hpp"
#include "Socket.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_SocketImpl::_SocketImpl() {
    init();
}

_SocketImpl::_SocketImpl(FileDescriptor fd) {
    init();
    mSock = fd;
}

_SocketImpl::_SocketImpl(InetAddress address, SocketOption option) {
    init();
    this->mAddress = address;
    this->mOption = option;
    if(option == nullptr || (mBuffSize = option->getRcvBuffSize()) == -1) {
        mBuffSize = st(SocketOption)::DefaultBuffSize;
    }
}

void _SocketImpl::init() {
    mSock = nullptr;
    mAddress = nullptr;
    mOption = nullptr;
    mBuffSize = st(SocketOption)::DefaultBuffSize;
}

int _SocketImpl::close() {
    return mSock->close();
}

FileDescriptor _SocketImpl::getFileDescriptor() {
    return mSock;
}

InetAddress _SocketImpl::getInetAddress() {
    return mAddress;
}

int _SocketImpl::write(ByteArray data,int start,int length) {
    int size = (length == -1?data->size() - start:length);
    if(size > data->size()) {
        Trigger(IllegalArgumentException,"oversize");
    }

    return ::write(mSock->getFd(),data->toValue() + start,size);
}

int _SocketImpl::read(ByteArray data,int start,int length) {
    int size = (length == -1?data->size() - start:length);
    int destLength = ((start + size) > data->size())?(data->size() - start):size;

    return ::read(mSock->getFd(),data->toValue() + start,destLength);
}

ByteArray _SocketImpl::read() {
    ByteArray buff = createByteArray(mBuffSize);
    int length = ::read(mSock->getFd(), buff->toValue(), mBuffSize);
    buff->quickShrink(length);
    return buff;
}

} // namespace obotcha
