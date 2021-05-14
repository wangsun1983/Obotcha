#include "SocketBuilder.hpp"

namespace obotcha {

_SocketBuilder* _SocketBuilder::setAddress(InetAddress addr) {
    address = addr;
    return this;
}

_SocketBuilder* _SocketBuilder::setOption(SocketOption o) {
    if(o != nullptr) {
        option = o;
    }
    return this;
}

_SocketBuilder* _SocketBuilder::setFd(int f) {
    fd = f;
    return this;
}

_SocketBuilder::_SocketBuilder() {
    address = createInetAddress();
    fd = -1;
    option = nullptr;
}

Socket _SocketBuilder::newSocket() {
    if(fd == -1) {
        return createSocket(st(Socket)::Tcp,address,option);
    }

    Socket s = createSocket(fd);
    s->setInetAddress(address);
    return s;
}

Socket _SocketBuilder::newDatagramSocket() {
    return createSocket(st(Socket)::Udp,address,option);
}

Socket _SocketBuilder::newLocalSocket() {
    if(fd == -1) {
        return createSocket(st(Socket)::Local,address,option);
    }

    Socket s = createSocket(fd);
    s->setInetAddress(address);
    return s;
}

ServerSocket _SocketBuilder::newServerSocket() {
    return createServerSocket(st(Socket)::Tcp,address,option);
}

ServerSocket _SocketBuilder::newServerLocalSocket() {
    return createServerSocket(st(Socket)::Local,address,option);
}
    


}