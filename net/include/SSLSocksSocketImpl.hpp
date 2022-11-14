#ifndef __OBOTCHA_SSL_SOCKS_SOCKET_IMPL_HPP__
#define __OBOTCHA_SSL_SOCKS_SOCKET_IMPL_HPP__


#include "Object.hpp"
#include "SocketImpl.hpp"
#include "SSLSocketContext.hpp"

namespace obotcha {

class _SSLServerSocketImpl;

DECLARE_CLASS(SSLSocksSocketImpl) IMPLEMENTS(SocketImpl) {
public:
    friend class _SSLServerSocketImpl;
    
    //_SSLSocksSocketImpl(String certificatePath,String keyPath,SocketImpl s);
    //_SSLSocksSocketImpl(String certificatePath,String keyPath,InetAddress address,SocketOption option);

    //_SSLSocksSocketImpl(InetAddress address,SocketOption option);
    //_SSLSocksSocketImpl(SocketImpl impl);

    _SSLSocksSocketImpl(SocketImpl s,SocketOption option);
    _SSLSocksSocketImpl(InetAddress address,SocketOption option);
    _SSLSocksSocketImpl(SocketImpl impl);

    SSLSocketContext getSSLContext();

    int connect();

    //int read(ByteArray);
    //int write(ByteArray);

    int close();
    
    int write(ByteArray,int start = 0,int length = -1);
    int read(ByteArray,int start = 0,int length = -1);
    ByteArray read();

    FileDescriptor getFileDescriptor();

private:
    void init(String,String);

    static int DefaultConnectNum;

    //SSL *mSSL;
    //SSL_CTX *mCtx;

    //String mCertificate;
    //String mKey;
    SSLSocketContext mContext;

    SocketImpl mSocket;
};

}

#endif