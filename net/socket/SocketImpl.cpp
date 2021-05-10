#include "SocketImpl.hpp"

namespace obotcha {

_SocketImpl::_SocketImpl(int fd) {
    sock = fd;
    mBuffSize = -1;
    mBuff = nullptr;
}

_SocketImpl::_SocketImpl(InetAddress address,SocketOption option) {
    this->address = address;
    this->option = option;
    this->mBuff = nullptr;
    this->mBuffSize = -1;

    if(option != nullptr && option->getBuffSize() >= 0 ) {
        mBuffSize = option->getBuffSize();
        mBuff = new byte[mBuffSize];
    }
}

int _SocketImpl::close() {
    if(sock != -1) {
        ::close(sock);
        sock = -1;
    }

    if(mBuff != nullptr) {
        delete []mBuff;
    }
    
    return 0;
}

ByteArray _SocketImpl::receive() {
    if(mBuffSize > 0) {
        int length = ::read(sock,mBuff,mBuffSize);
        return createByteArray(mBuff,length);
    }

    byte buff[1024];
    int length = ::read(sock,buff,1024);
    return createByteArray(buff,length);
}

int _SocketImpl::getFd() {
    return this->sock;
}

InetAddress _SocketImpl::getInetAddress() {
    return address;
}

void _SocketImpl::setInetAddress(InetAddress addr) {
    address = addr;
}

}
