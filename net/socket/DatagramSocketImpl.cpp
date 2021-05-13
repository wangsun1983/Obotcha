#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <stddef.h>

#include "DatagramSocketImpl.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_DatagramSocketImpl::_DatagramSocketImpl(InetAddress address,SocketOption option):_SocketImpl(address,option) {
    mSockAddr.sin_family = AF_INET;
    mSockAddr.sin_port = htons(address->getPort());
    
    if(address != nullptr) {
        mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
    } else {
        mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    sock = TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_DGRAM, 0));
    if(sock < 0) {
        Trigger(InitializeException,"Datagram Socket create failed");
    }
    
    setOptions();
}

int _DatagramSocketImpl::connect() {
    //nothing
    return 0;
}

int _DatagramSocketImpl::bind() {
    return ::bind(sock,(struct sockaddr*)&mSockAddr,sizeof(mSockAddr));
}


}