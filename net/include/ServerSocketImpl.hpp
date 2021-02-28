#ifndef __OBOTCHA_SERVER_SOCKET_IMPL_HPP__
#define __OBOTCHA_SERVER_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketImpl.hpp"
#include "Error.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ServerSocketImpl) IMPLEMENTS(SocketImpl) {
public:
    _ServerSocketImpl(InetAddress address, int port,SocketOption option);
    int bind();
    
};

}

#endif