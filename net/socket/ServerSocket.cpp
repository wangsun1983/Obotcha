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

int _ServerSocket::getFd() {
    return mSock->getFd();
}

int _ServerSocket::close() {
    return mSock->close();
}

}