#ifndef __OBOTCHA_SERVER_LOCAL_SOCKET_IMPL_HPP__
#define __OBOTCHA_SERVER_LOCAL_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "LocalSocketImpl.hpp"
#include "Socket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ServerLocalSocketImpl) IMPLEMENTS(LocalSocketImpl) {
public:
    _ServerLocalSocketImpl(InetAddress address,SocketOption option);
    int bind();
    Socket accept();
    
};

}

#endif