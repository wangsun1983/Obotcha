#include "SocketBuilder.hpp"
#include "InetAddress.hpp"

#include "DatagramSocketImpl.hpp"

namespace obotcha {

_SocketBuilder *_SocketBuilder::setAddress(InetAddress addr) {
    mAddress = addr;
    return this;
}

_SocketBuilder *_SocketBuilder::setOption(SocketOption o) {
    if (o != nullptr) {
        mOption = o;
    }
    return this;
}

_SocketBuilder *_SocketBuilder::setFileDescriptor(FileDescriptor f) {
    mFd = f;
    return this;
}

_SocketBuilder* _SocketBuilder::setAsync(bool s) {
    mIsAsync = s;
    return this;
}

Socket _SocketBuilder::newSocket() {
    if (mFd == nullptr) {
        return Socket::New(st(Net)::Protocol::Tcp, 
                            mAddress, mOption,mIsAsync,mPool);
    }
    
    return Socket::New(mFd,mAddress,mPool);
}

_SocketBuilder* _SocketBuilder::setAsyncPool(AsyncOutputChannelPool pool) {
    mPool = pool;
    mIsAsync = true;
    return this;
}

Socket _SocketBuilder::newDatagramSocket() {
    if(mFd == nullptr) {
        return Socket::New(st(Net)::Protocol::Udp, mAddress, mOption);
    } else {
        auto datagramImpl = DatagramSocketImpl::New(mFd,mAddress,mOption);
        return Socket::New(datagramImpl,mAddress,mPool);
    }
}

Socket _SocketBuilder::newSSLSocket() {
    return Socket::New(st(Net)::Protocol::Ssl,
                        mAddress,
                        mOption,
                        mIsAsync,
                        mPool);
}

ServerSocket _SocketBuilder::newServerSocket() {
    return ServerSocket::New(st(Net)::Protocol::Tcp, mAddress, mOption);
}

ServerSocket _SocketBuilder::newSSLServerSocket() {
    return ServerSocket::New(st(Net)::Protocol::Ssl, 
                              mAddress, 
                              mOption);
}

} // namespace obotcha