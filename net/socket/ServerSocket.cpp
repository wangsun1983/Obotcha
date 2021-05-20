#include "ServerSocket.hpp"
#include "ServerSocketImpl.hpp"
#include "ServerLocalSocketImpl.hpp"

namespace obotcha {
_ServerSocket::_ServerSocket(int type,InetAddress address,SocketOption option) {
    switch(type) {
        case st(Socket)::Tcp:
            this->mSock = createServerSocketImpl(address,option);
        break;

        case st(Socket)::Local:
            this->mSock = createServerLocalSocketImpl(address,option);
        break;
    }
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
    

}