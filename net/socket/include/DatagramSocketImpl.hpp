#ifndef __OBOTCHA_DATAGRAM_SOCKET_IMPL_HPP__
#define __OBOTCHA_DATAGRAM_SOCKET_IMPL_HPP__

#include "Object.hpp"
#include "SocketImpl.hpp"
#include "SocketOption.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_CLASS(DatagramSocketImpl) IMPLEMENTS(SocketImpl) {
public:
    _DatagramSocketImpl();
    _DatagramSocketImpl(InetAddress address,SocketOption option);
    _DatagramSocketImpl(FileDescriptor,InetAddress,SocketOption);
    sp<_Socket> recvDatagram(ByteArray) override;
    int connect() override;
    int bind() override;
    ssize_t write(ByteArray data,uint64_t start = 0,uint64_t length = 0) override;
};

}

#endif