#include "ServerSocketImpl.hpp"

namespace obotcha {

_ServerSocketImpl::_ServerSocketImpl(InetAddress address,SocketOption option):_SocksSocketImpl(address,option) {
    //TODO
}

int _ServerSocketImpl::bind() {
    printf("server socket impl is %d \n",sock);
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

    return 0;
}
    

}