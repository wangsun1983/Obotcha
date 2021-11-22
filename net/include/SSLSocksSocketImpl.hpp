#ifndef __OBOTCHA_SSL_SOCKS_SOCKET_IMPL_HPP__
#define __OBOTCHA_SSL_SOCKS_SOCKET_IMPL_HPP__

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

class _SSLServerSocketImpl;

DECLARE_CLASS(SSLSocksSocketImpl) IMPLEMENTS(SocketImpl) {
public:
    friend class _SSLServerSocketImpl;
    _SSLSocksSocketImpl(String certificatePath,String keyPath,InetAddress address,SocketOption option,bool isServer = false);
    _SSLSocksSocketImpl(String certificatePath,String keyPath,SocketImpl,bool isServer = false);
    int connect();

    //int read(ByteArray);
    //int write(ByteArray);

    int close();
    
    int write(ByteArray,int start = 0,int length = -1);
    int read(ByteArray,int start = 0,int length = -1);
    ByteArray read();

    FileDescriptor getFileDescriptor();

private:
    void init(String certificatePath,String keyPath,bool isServer);

    static int DefaultConnectNum;

    SSL *mSSL;
    SSL_CTX *mCtx;

    String mCertificate;
    String mKey;

    SocketImpl mSocket;
};

}

#endif