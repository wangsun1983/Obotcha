#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ServerLocalSocketImpl.hpp"
#include "InetAddress.hpp"
#include "SocketBuilder.hpp"

namespace obotcha {

_ServerLocalSocketImpl::_ServerLocalSocketImpl(InetAddress address,SocketOption option):
                                                _LocalSocketImpl(address,option) {

}

int _ServerLocalSocketImpl::bind() {
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);

    if( ::bind(sock->getFd(), (struct sockaddr *)&serverAddr, len) < 0) {
        if(errno == EADDRINUSE) {
            return -NetAddrAlreadyUseFail; 
        }

        return -NetBindFail;
    }
    
    int connectNum = 32;
    if(option != nullptr) {
        connectNum = option->getConnectionNum();
    }
    if(listen(sock->getFd(), connectNum) < 0) {
        return -NetListenFail;
    }
    
    return 0;
}

Socket _ServerLocalSocketImpl::accept() {
    struct sockaddr_in client_address;
    socklen_t client_addrLength = sizeof(struct sockaddr_in);
    int clientfd = ::accept(sock->getFd(),( struct sockaddr* )&client_address, &client_addrLength );
    if(clientfd > 0) {
        InetAddress address = createInetAddress(createString(inet_ntoa(client_address.sin_addr)),
                                                ntohs(client_address.sin_port));
        
        return createSocketBuilder()
                ->setAddress(address)
                ->setFileDescriptor(createFileDescriptor(clientfd))
                ->newLocalSocket();
    }

    return nullptr;
}
    
}
