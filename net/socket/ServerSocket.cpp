#include "ServerSocket.hpp"
#include "ServerSocketImpl.hpp"
#include "SSLServerSocketImpl.hpp"

#include "Log.hpp"

namespace obotcha {

_ServerSocket::_ServerSocket(st(Net)::Protocol type, InetAddress address,
                             SocketOption option) {
    switch (type) {
        case st(Net)::Protocol::Tcp:
            mSockImpl = createServerSocketImpl(address, option);
            break;
        
        case st(Net)::Protocol::Ssl:
            mSockImpl = createSSLServerSocketImpl(address,option);
            break;

        default:
            LOG(ERROR)<<"ServerSocket unkonw type:"<<static_cast<int>(type);
            break;
    }

    mAddr = address;
}

Socket _ServerSocket::accept() { 
    return mSockImpl->accept(); 
}

} // namespace obotcha