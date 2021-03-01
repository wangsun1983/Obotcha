#include "SocketBuilder.hpp"

namespace obotcha {

_SocketBuilder* _SocketBuilder::setAddress(InetAddress addr) {
    address = addr;
}

_SocketBuilder* _SocketBuilder::setPort(int p) {
    port = p;
}

_SocketBuilder* _SocketBuilder::setOption(SocketOption o) {
    option = o;
}

_SocketBuilder::_SocketBuilder() {
    address = createInetAddress();
}

Socket _SocketBuilder::newSocket() {
    return createSocket(st(Socket)::Tcp,address,port,option);
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