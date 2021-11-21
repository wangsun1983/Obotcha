#include "SocketBuilder.hpp"
#include "Inet4Address.hpp"

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
}

_SocketBuilder* _SocketBuilder::setSSLKeyPath(String path) {
    mKeyPath = path;
}

_SocketBuilder::_SocketBuilder() {
    address = createInet4Address(st(InetAddress)::DefaultPort);
    fd = nullptr;
    option = nullptr;
}

Socket _SocketBuilder::newSocket() {
    if (fd == nullptr) {
        return createSocket(st(Socket)::Tcp, address, option);
    }

    Socket s = createSocket(fd);
    s->setInetAddress(address);
    return s;
}

Socket _SocketBuilder::newDatagramSocket() {
    return createSocket(st(Socket)::Udp, address, option);
}

Socket _SocketBuilder::newLocalSocket() {
    if (fd == nullptr) {
        return createSocket(st(Socket)::Local, address, option);
    }

    Socket s = createSocket(fd);
    s->setInetAddress(address);
    return s;
}

Socket _SocketBuilder::newSSLSocket() {
    return createSocket(st(Socket)::SSL,address,option,mCertificatePath,mKeyPath);
}

ServerSocket _SocketBuilder::newServerSocket() {
    return createServerSocket(st(Socket)::Tcp, address, option);
}

ServerSocket _SocketBuilder::newServerLocalSocket() {
    return createServerSocket(st(Socket)::Local, address, option);
}

ServerSocket _SocketBuilder::newSSLServerSocket() {
    return createServerSocket(st(Socket)::SSL, address, option,mCertificatePath,mKeyPath);
}

} // namespace obotcha