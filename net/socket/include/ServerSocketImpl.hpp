#ifndef __OBOTCHA_SERVER_SOCKET_IMPL_HPP__
#define __OBOTCHA_SERVER_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "SocksSocketImpl.hpp"
#include "Socket.hpp"

namespace obotcha {

DECLARE_CLASS(ServerSocketImpl) IMPLEMENTS(SocksSocketImpl) {
public:
    _ServerSocketImpl(InetAddress address,SocketOption option);
    int bind() override;
    Socket accept() override;

private:
    static int DefaultConnectNum;
    
};

}

#endif