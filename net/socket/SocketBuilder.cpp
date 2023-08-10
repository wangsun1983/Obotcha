#include "SocketBuilder.hpp"
#include "Inet4Address.hpp"

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
        return createSocket(st(Net)::Protocol::Tcp, 
                            mAddress, mOption,mIsAsync,mPool);
    }
    
    return createSocket(mFd,mAddress,mPool);
}

_SocketBuilder* _SocketBuilder::setAsyncPool(AsyncOutputChannelPool pool) {
    mPool = pool;
    mIsAsync = true;
    return this;
}

Socket _SocketBuilder::newDatagramSocket() {
    if(mFd == nullptr) {
        return createSocket(st(Net)::Protocol::Udp, mAddress, mOption);
    } else {
        auto datagramImpl = createDatagramSocketImpl(mFd,mAddress,mOption);
        return createSocket(datagramImpl,mAddress,mPool);
    }
}

Socket _SocketBuilder::newSSLSocket() {
    return createSocket(st(Net)::Protocol::Ssl,
                        mAddress,
                        mOption,
                        mIsAsync,
                        mPool);
}

ServerSocket _SocketBuilder::newServerSocket() {
    return createServerSocket(st(Net)::Protocol::Tcp, mAddress, mOption);
}

ServerSocket _SocketBuilder::newSSLServerSocket() {
    return createServerSocket(st(Net)::Protocol::Ssl, 
                              mAddress, 
                              mOption);
}

} // namespace obotcha