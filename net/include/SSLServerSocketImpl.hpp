#ifndef __OBOTCHA_SSL_SERVER_SOCKET_IMPL_HPP__
#define __OBOTCHA_SSL_SERVER_SOCKET_IMPL_HPP__

extern "C" {
#include "openssl/ssl.h"
#include "openssl/err.h"
}

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocksSocketImpl.hpp"
#include "ServerSocketImpl.hpp"
#include "Socket.hpp"
#include "Error.hpp"

namespace obotcha {

DECLARE_CLASS(SSLServerSocketImpl) IMPLEMENTS(SocketImpl) {
public:
    _SSLServerSocketImpl(String certificatePath,String keyPath,InetAddress address,SocketOption option);
    ~_SSLServerSocketImpl();
    int bind();
    int close();
    Socket accept();
    FileDescriptor getFileDescriptor();

private:
    static int DefaultConnectNum;

    SSL *mSSL;
    SSL_CTX *mCtx;

    String mCertificate;
    String mKey;

    ServerSocketImpl mSocket;
    
};

}

#endif