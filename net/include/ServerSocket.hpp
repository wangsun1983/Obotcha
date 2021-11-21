#ifndef __OBOTCHA_SERVER_SOCKET_HPP__
#define __OBOTCHA_SERVER_SOCKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "FileDescriptor.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"

namespace obotcha {

DECLARE_CLASS(ServerSocket) {
  public:
    _ServerSocket(int, InetAddress address, SocketOption option,String certificatePath = nullptr,String keyPath = nullptr);
    InetAddress getInetAddress();
    int bind();
    FileDescriptor getFileDescriptor();
    int close();

    // add
    Socket accept();

  private:
    SocketImpl mSock;
    InetAddress mAddr;
};

} // namespace obotcha

#endif