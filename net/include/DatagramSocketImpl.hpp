#ifndef __OBOTCHA_DATAGRAM_SOCKET_IMPL_HPP__
#define __OBOTCHA_DATAGRAM_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketImpl.hpp"
#include "OutputStream.hpp"
#include "SocketOption.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_CLASS(DatagramSocketImpl) IMPLEMENTS(SocketImpl){
public:
    _DatagramSocketImpl();
    _DatagramSocketImpl(InetAddress address,SocketOption option);
    sp<_Socket> recvDatagram(ByteArray);
    int connect();
    int bind();

    int write(ByteArray data,int start = 0,int length = -1);

    
};

}

#endif