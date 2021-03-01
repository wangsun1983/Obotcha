#ifndef __OBOTCHA_SERVER_SOCKET_IMPL_HPP__
#define __OBOTCHA_SERVER_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocksSocketImpl.hpp"
#include "Error.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ServerSocketImpl) IMPLEMENTS(SocksSocketImpl) {
public:
    _ServerSocketImpl(InetAddress address, int port,SocketOption option);
    int bind();
    
};

}

#endif