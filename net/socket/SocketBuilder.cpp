#include "SocketBuilder.hpp"
#include "Inet4Address.hpp"
#include "NetProtocol.hpp"
#include "DatagramSocketImpl.hpp"

namespace obotcha {

_SocketBuilder *_SocketBuilder::setAddress(InetAddress addr) {
    address = addr;
    return this;
}

_SocketBuilder *_SocketBuilder::setOption(SocketOption o) {
    if (o != nullptr) {
        option = o;
    }
    return this;
}

_SocketBuilder *_SocketBuilder::setFileDescriptor(FileDescriptor f) {
    fd = f;
    return this;
}

_SocketBuilder* _SocketBuilder::setSSLCretificatePath(String path) {
    mCertificatePath = path;
    return this;
}

_SocketBuilder* _SocketBuilder::setSSLKeyPath(String path) {
    mKeyPath = path;
    return this;
}

_SocketBuilder* _SocketBuilder::setAsync(bool s) {
    mIsAsync = s;
    return this;
}

_SocketBuilder::_SocketBuilder() {
    address = createInet4Address(st(InetAddress)::DefaultPort);
    fd = nullptr;
    option = nullptr;
}

Socket _SocketBuilder::newSocket() {
    if (fd == nullptr) {
        return createSocket(st(NetProtocol)::Tcp, address, option,nullptr,nullptr,mIsAsync,mPool);
    }
    
    return createSocket(fd,mPool);
}

_SocketBuilder* _SocketBuilder::setAsyncPool(AsyncOutputChannelPool pool) {
    mPool = pool;
    mIsAsync = true;
    return this;
}

Socket _SocketBuilder::newDatagramSocket() {
    if(fd == nullptr) {
        return createSocket(st(NetProtocol)::Udp, address, option);
    } else {
        auto datagramImpl = createDatagramSocketImpl(fd,address,option);
        return createSocket(datagramImpl,mPool);
    }
}

Socket _SocketBuilder::newSSLSocket() {
    return createSocket(st(NetProtocol)::Ssl,address,option,mCertificatePath,mKeyPath,mIsAsync,mPool);
}

ServerSocket _SocketBuilder::newServerSocket() {
    return createServerSocket(st(NetProtocol)::Tcp, address, option);
}

ServerSocket _SocketBuilder::newSSLServerSocket() {
    return createServerSocket(st(NetProtocol)::Ssl, address, option,mCertificatePath,mKeyPath);
}

} // namespace obotcha