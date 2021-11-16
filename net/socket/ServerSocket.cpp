#include "ServerSocket.hpp"
#include "ServerLocalSocketImpl.hpp"
#include "ServerSocketImpl.hpp"

namespace obotcha {

_ServerSocket::_ServerSocket(int type, InetAddress address,
                             SocketOption option) {
    switch (type) {
        case st(Socket)::Tcp:
            this->mSock = createServerSocketImpl(address, option);
            break;

        case st(Socket)::Local:
            this->mSock = createServerLocalSocketImpl(address, option);
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