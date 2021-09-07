#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ServerSocketImpl.hpp"
#include "SocketBuilder.hpp"

namespace obotcha {

int _ServerSocketImpl::DefaultConnectNum = 16;

_ServerSocketImpl::_ServerSocketImpl(InetAddress address,SocketOption option):_SocketImpl(address,option),_SocksSocketImpl(address,option) {
}

int _ServerSocketImpl::bind() {
    if(::bind(sock->getFd(), (struct sockaddr *)&mSockAddr, sizeof(mSockAddr)) < 0) {
        return -NetBindFail;
    }

    int connectNum = DefaultConnectNum;
    if(option != nullptr) {
        connectNum = option->getConnectionNum();
    }
    
    if(listen(sock->getFd(), connectNum) < 0) {
        return -NetListenFail;
    }

    return 0;
}

Socket _ServerSocketImpl::accept() {
    struct sockaddr_in client_address;
    socklen_t client_addrLength = sizeof(struct sockaddr_in);
    int clientfd = ::accept(sock->getFd(),( struct sockaddr* )&client_address, &client_addrLength );
    if(clientfd > 0) {
        InetAddress address = createInetAddress(createString(inet_ntoa(client_address.sin_addr)),
                                                ntohs(client_address.sin_port));
        
        return createSocketBuilder()
                ->setAddress(address)
                ->setFileDescriptor(createFileDescriptor(clientfd))
                ->newSocket();
    }

    return nullptr;
}

}
