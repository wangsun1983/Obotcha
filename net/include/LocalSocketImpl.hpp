#ifndef __OBOTCHA_LOCAL_SOCKET_IMPL_HPP__
#define __OBOTCHA_LOCAL_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketImpl.hpp"
#include "SocketOption.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(LocalSocketImpl) IMPLEMENTS(SocketImpl){
public:
    _LocalSocketImpl(InetAddress address, SocketOption option);
    int connect();

protected:
    struct sockaddr_un serverAddr;

};

}

#endif