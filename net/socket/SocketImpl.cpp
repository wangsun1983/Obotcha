#include "SocketImpl.hpp"
#include "Socket.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_SocketImpl::_SocketImpl(FileDescriptor fd):mSock(fd) {
}

_SocketImpl::_SocketImpl(InetAddress address, SocketOption option):mAddress(address),mOption(option) {
    mBuffSize = (option == nullptr)?st(SocketOption)::DefaultBuffSize:
                                option->getRcvBuffSize();
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

int _SocketImpl::write(ByteArray data,uint64_t start,uint64_t length) {
    auto size = computeSutiableSize(data,start,length);
    return ::write(mSock->getFd(),data->toValue() + start,size);
}

int _SocketImpl::read(ByteArray data,uint64_t start,uint64_t length) {
    auto size = computeSutiableSize(data,start,length);
    return ::read(mSock->getFd(),data->toValue() + start,size);
}

ByteArray _SocketImpl::read() {
    ByteArray buff = createByteArray(mBuffSize);
    ssize_t length = ::read(mSock->getFd(), buff->toValue(), mBuffSize);
    if(length > 0) {
        buff->quickShrink(length);
        return buff;
    }
    return nullptr;
}

int _SocketImpl::computeSutiableSize(ByteArray data,uint64_t start,uint64_t length) const {
    auto rest = data->size() - start;
    return (length == 0)?rest:std::min(rest,length);
}

} // namespace obotcha
