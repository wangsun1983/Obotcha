#include "ServerSocket.hpp"
#include "ServerSocketImpl.hpp"
#include "SSLServerSocketImpl.hpp"
#include "NetProtocol.hpp"
#include "Log.hpp"

namespace obotcha {

_ServerSocket::_ServerSocket(int type, InetAddress address,
                             SocketOption option) {
    switch (type) {
        case st(NetProtocol)::Tcp:
            mSockImpl = createServerSocketImpl(address, option);
            break;
        
        case st(NetProtocol)::Ssl:
            mSockImpl = createSSLServerSocketImpl(address,option);
            break;

        default:
            LOG(ERROR)<<"ServerSocket unkonw type:"<<type;
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