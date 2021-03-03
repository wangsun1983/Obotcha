#ifndef __OBOTCHA_SOCKET_BUILDER_HPP__
#define __OBOTCHA_SOCKET_BUILDER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"
#include "ServerSocket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketBuilder) {
public:
    _SocketBuilder();
    
    _SocketBuilder* setAddress(InetAddress);
    _SocketBuilder* setOption(SocketOption);
    _SocketBuilder* setFd(int);

    Socket newSocket();
    Socket newDatagramSocket();
    Socket newLocalSocket();
    ServerSocket newServerSocket();
    ServerSocket newServerLocalSocket();
    
private:
    InetAddress address;
    SocketOption option;
    int fd;
};

}

#endif