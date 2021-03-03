#include "ServerLocalSocketImpl.hpp"

namespace obotcha {

_ServerLocalSocketImpl::_ServerLocalSocketImpl(InetAddress address,SocketOption option):
                                                _LocalSocketImpl(address,option) {

}

int _ServerLocalSocketImpl::bind() {
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);

    if( ::bind(sock, (struct sockaddr *)&serverAddr, len) < 0) {
        if(errno == EADDRINUSE) {
            return -NetAddrAlreadyUseFail; 
        }

        return -NetBindFail;
    }
    
    int connectNum = 20;
    if(option != nullptr) {
        connectNum = option->getConnectionNum();
    }
    if(listen(sock, connectNum) < 0) {
        return -NetListenFail;
    }
    
    return 0;
}
    
}
