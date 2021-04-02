#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ServerSocketImpl.hpp"
#include "SocketBuilder.hpp"

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

Socket _ServerSocketImpl::accept() {
    struct sockaddr_in client_address;
    socklen_t client_addrLength = sizeof(struct sockaddr_in);
    int clientfd = ::accept(sock,( struct sockaddr* )&client_address, &client_addrLength );
    if(clientfd > 0) {
        InetAddress address = createInetAddress(createString(inet_ntoa(client_address.sin_addr)),
                                                ntohs(client_address.sin_port));
        
        return createSocketBuilder()->setAddress(address)->setFd(clientfd)->newSocket();
    }

    return nullptr;
}



}
