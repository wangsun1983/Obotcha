#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <stddef.h>

#include "DatagramSocketImpl.hpp"

namespace obotcha {

_DatagramSocketImpl::_DatagramSocketImpl(InetAddress address,SocketOption option):_SocketImpl(address,option) {
    mSockAddr.sin_family = AF_INET;
    mSockAddr.sin_port = htons(address->getPort());
    
    if(address != nullptr) {
        printf("address is %s \n",address->getAddress()->toChars());
        mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
    } else {
        printf("address2 is null \n");
        mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
}

int _DatagramSocketImpl::connect() {
    //nothing
    return 0;
}

int _DatagramSocketImpl::bind() {
    return ::bind(sock,(struct sockaddr*)&mSockAddr,sizeof(mSockAddr));
}


}