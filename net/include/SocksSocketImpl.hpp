#ifndef __OBOTCHA_SOCKS_SOCKET_IMPL_HPP__
#define __OBOTCHA_SOCKS_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketImpl.hpp"
#include "OutputStream.hpp"
#include "SocketOption.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocksSocketImpl) IMPLEMENTS(SocketImpl){
public:
    _SocksSocketImpl(InetAddress host,SocketOption option = nullptr);
    int connect();
    //~_SocksSocketImpl();
};

}

#endif