/**
 * @file ServerSocket.cpp
 * @brief This class implements server sockets. A server socket waits for
 * requests to come in over the network. It performs some operation
 * based on that request, and then possibly returns a result to the requester.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-17
 * @license none
 */

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