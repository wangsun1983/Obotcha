#include "SocketBuilder.hpp"

namespace obotcha {

_SocketBuilder* _SocketBuilder::setAddress(InetAddress addr) {
    address = addr;
    return this;
}

_SocketBuilder* _SocketBuilder::setPort(int p) {
    port = p;
    return this;
}

_SocketBuilder* _SocketBuilder::setOption(SocketOption o) {
    option = o;
    return this;
}

_SocketBuilder* _SocketBuilder::setFd(int f) {
    fd = f;
    return this;
}

_SocketBuilder::_SocketBuilder() {
    address = createInetAddress();
    fd = -1;
}

Socket _SocketBuilder::newSocket() {
    if(fd == -1) {
        return createSocket(st(Socket)::Tcp,address,port,option);
    } 
    return createSocket(fd);
}

Socket _SocketBuilder::newDatagramSocket() {
    return createSocket(st(Socket)::Udp,nullptr,port,option);
}

Socket _SocketBuilder::newLocalSocket() {
    return createSocket(st(Socket)::Local,address,-1,option);
}

ServerSocket _SocketBuilder::newServerSocket() {
    return createServerSocket(st(Socket)::Tcp,address,port,option);
}

ServerSocket _SocketBuilder::newServerLocalSocket() {
    //TODO
}
    


}