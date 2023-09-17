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
    
    ssize_t write(ByteArray,uint64_t start = 0,uint64_t length = 0) override;
    ssize_t read(ByteArray,uint64_t start = 0,uint64_t length = 0) override;
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