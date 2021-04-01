#ifndef __OBOTCHA_DATAGRAM_SOCKET_IMPL_HPP__
#define __OBOTCHA_DATAGRAM_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketImpl.hpp"
#include "OutputStream.hpp"
#include "SocketOption.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(DatagramSocketImpl) IMPLEMENTS(SocketImpl){
public:
    _DatagramSocketImpl(InetAddress address,SocketOption option);
    int connect();
    int bind();

};

}

#endif