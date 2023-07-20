#ifndef __OBOTCHA_SOCKS_SOCKET_IMPL_HPP__
#define __OBOTCHA_SOCKS_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "SocketImpl.hpp"

namespace obotcha {

DECLARE_CLASS(SocksSocketImpl) IMPLEMENTS(SocketImpl){
public:
    explicit _SocksSocketImpl(InetAddress host,SocketOption option = nullptr);
    int connect();
};

}

#endif