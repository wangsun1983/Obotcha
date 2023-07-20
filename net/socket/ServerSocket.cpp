#include "ServerSocket.hpp"
#include "ServerSocketImpl.hpp"
#include "SSLServerSocketImpl.hpp"
#include "NetProtocol.hpp"

namespace obotcha {

_ServerSocket::_ServerSocket(int type, InetAddress address,
                             SocketOption option) {
    switch (type) {
        case st(NetProtocol)::Tcp:
            printf("ServerSocket,create tcp server socket \n");
            mSockImpl = createServerSocketImpl(address, option);
            break;
        
        case st(NetProtocol)::Ssl:
            printf("ServerSocket,create ssl server socket \n");
            mSockImpl = createSSLServerSocketImpl(address,option);
            break;
    }

    mAddr = address;
}

int _ServerSocket::bind() {
    printf("ServerSocket bind \n");
    return mSockImpl->bind(); 
}

Socket _ServerSocket::accept() { 
    return mSockImpl->accept(); 
}

} // namespace obotcha