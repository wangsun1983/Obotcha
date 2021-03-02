#include "ServerSocket.hpp"
#include "ServerSocketImpl.hpp"
#include "ServerLocalSocketImpl.hpp"

namespace obotcha {
_ServerSocket::_ServerSocket(int type,InetAddress address, int port,SocketOption option) {
    switch(type) {
        case st(Socket)::Tcp:
            this->mSock = createServerSocketImpl(address,port,option);
        break;

        case st(Socket)::Local:
            this->mSock = createServerLocalSocketImpl(address,port,option);
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
    printf("server socket close \n");
    return mSock->close();
}

}