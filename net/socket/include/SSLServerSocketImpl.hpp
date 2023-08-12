#ifndef __OBOTCHA_SSL_SERVER_SOCKET_IMPL_HPP__
#define __OBOTCHA_SSL_SERVER_SOCKET_IMPL_HPP__

extern "C" {
    #include "openssl/ssl.h"
    #include "openssl/err.h"
}

#include "Object.hpp"
#include "SocketImpl.hpp"
#include "ServerSocketImpl.hpp"
#include "SSLSocketContext.hpp"
#include "Socket.hpp"
#include "SocketOption.hpp"

namespace obotcha {

DECLARE_CLASS(SSLServerSocketImpl) IMPLEMENTS(SocketImpl) {
public:
    _SSLServerSocketImpl(InetAddress address,SocketOption option);
    ~_SSLServerSocketImpl() override = default;
    int bind() override;
    int close() override;
    Socket accept() override;
    FileDescriptor getFileDescriptor() override;

private:
    static int DefaultConnectNum;

    SSLSocketContext mSSLContext;
    ServerSocketImpl mSocket;
    
};

}

#endif