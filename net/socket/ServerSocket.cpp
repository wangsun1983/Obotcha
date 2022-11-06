#include "ServerSocket.hpp"
#include "ServerSocketImpl.hpp"
#include "SSLServerSocketImpl.hpp"
#include "NetProtocol.hpp"

namespace obotcha {

_ServerSocket::_ServerSocket(int type, InetAddress address,
                             SocketOption option,String certificatePath,String keyPath) {
    switch (type) {
        case st(NetProtocol)::Tcp:
            this->mSock = createServerSocketImpl(address, option);
            break;
        
        case st(NetProtocol)::Ssl:
            this->mSock = createSSLServerSocketImpl(certificatePath,keyPath,address,option);
            break;
    }

    mAddr = address;
}

InetAddress _ServerSocket::getInetAddress() {
    return mAddr;
}

int _ServerSocket::bind() { 
    return mSock->bind(); 
}

FileDescriptor _ServerSocket::getFileDescriptor() {
    return mSock->getFileDescriptor();
}

int _ServerSocket::close() { 
    return mSock->close(); 
}

Socket _ServerSocket::accept() { 
    return mSock->accept(); 
}

} // namespace obotcha