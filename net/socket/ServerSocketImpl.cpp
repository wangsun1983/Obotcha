#include "ServerSocketImpl.hpp"

namespace obotcha {

_ServerSocketImpl::_ServerSocketImpl(InetAddress address, int port,SocketOption option):_SocketImpl(address,port,option) {
    //TODO
}

int _ServerSocketImpl::bind() {
    if(::bind(sock, (struct sockaddr *)&mSockAddr, sizeof(mSockAddr)) < 0) {
        return -NetBindFail;
    }

    int mConnectionNum = 20;
    if(option != nullptr) {
        mConnectionNum = option->getConnectionNum();
    }
    
    if(listen(sock, mConnectionNum) < 0) {
        return -NetListenFail;
    }
}
    

}
