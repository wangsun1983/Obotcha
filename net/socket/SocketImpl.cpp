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

void _SocketImpl::setInetAddress(InetAddress addr) {
    mAddress = addr;
}

int _SocketImpl::write(ByteArray data,int start,int length) {
    auto size = computeSutiableSize(data,start,length);
    return ::write(mSock->getFd(),data->toValue() + start,size);
}

int _SocketImpl::read(ByteArray data,int start,int length) {
    auto size = computeSutiableSize(data,start,length);
    return ::read(mSock->getFd(),data->toValue() + start,size);
}

ByteArray _SocketImpl::read() {
    ByteArray buff = createByteArray(mBuffSize);
    int length = ::read(mSock->getFd(), buff->toValue(), mBuffSize);
    if(length > 0) {
        buff->quickShrink(length);
        return buff;
    }
    return nullptr;
}

int _SocketImpl::computeSutiableSize(ByteArray data,int start,int length) {
    int rest = data->size() - start;
    return (length == 0)?rest:std::min(rest,length);
}

} // namespace obotcha
