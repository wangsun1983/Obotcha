#ifndef __OBOTCHA_SERVER_SOCKET_HPP__
#define __OBOTCHA_SERVER_SOCKET_HPP__

#include "Object.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"
#include "Net.hpp"

namespace obotcha {

DECLARE_CLASS(ServerSocket) IMPLEMENTS(Socket) {
  public:
    _ServerSocket(st(Net)::Protocol, InetAddress address, 
                  SocketOption option);
    Socket accept();

  private:
    InetAddress mAddr;
};

} // namespace obotcha

#endif