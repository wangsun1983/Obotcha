#ifndef __OBOTCHA_SERVER_SOCKET_HPP__
#define __OBOTCHA_SERVER_SOCKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Socket.hpp"
#include "InetAddress.hpp"
#include "SocketOption.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ServerSocket) {
public:
    _ServerSocket(int,InetAddress address, int port,SocketOption option);
    int bind();
    int getFd();
    int close();
private:
    SocketImpl mSock;
};

}

#endif