#include "ServerSocket.hpp"
#include "ServerSocketImpl.hpp"
#include "SSLServerSocketImpl.hpp"
#include "NetProtocol.hpp"

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
    }

    mAddr = address;
}

//InetAddress _ServerSocket::getInetAddress() {
//    return mAddr;
//}

int _ServerSocket::bind() { 
    return mSockImpl->bind(); 
}

//FileDescriptor _ServerSocket::getFileDescriptor() {
//    return mSock->getFileDescriptor();
//}

int _ServerSocket::close() { 
    return mSockImpl->close(); 
}

Socket _ServerSocket::accept() { 
    return mSockImpl->accept(); 
}

} // namespace obotcha