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
    
    _SSLSocksSocketImpl(SocketImpl s,SocketOption option);
    _SSLSocksSocketImpl(InetAddress address,SocketOption option);
    explicit _SSLSocksSocketImpl(SocketImpl impl);

    SSLSocketContext getSSLContext();

    int connect() override;

    int close() override;
    
    int write(ByteArray,int start = 0,int length = 0) override;
    int read(ByteArray,int start = 0,int length = 0) override;
    ByteArray read() override;
    FileDescriptor getFileDescriptor() override;

private:
    void init(String,String);

    static int DefaultConnectNum;

    SSLSocketContext mContext;

    SocketImpl mSocket;
};

}

#endif