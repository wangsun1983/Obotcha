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
    ~_SSLServerSocketImpl();
    int bind();
    int close();
    Socket accept();
    FileDescriptor getFileDescriptor();

private:
    static int DefaultConnectNum;

    SSLSocketContext mSSLContext;
    SocketOption mOption;
    // String mCertificate;
    // String mKey;

    ServerSocketImpl mSocket;
    
};

}

#endif