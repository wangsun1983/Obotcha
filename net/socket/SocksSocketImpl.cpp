#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <stddef.h>
#include <unistd.h>

#include "SocksSocketImpl.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "System.hpp"

namespace obotcha {

//socket
_SocksSocketImpl::_SocksSocketImpl(InetAddress address,SocketOption option):_SocketImpl(address,option){
    mSockAddr.sin_family = PF_INET;
    mSockAddr.sin_port = htons(address->getPort());
    
    if(address != nullptr 
        && address->getAddress() != nullptr 
        && !address->getAddress()->equalsIgnoreCase(st(InetAddress)::LocalHost)) {
        mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
    } else {
        mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    this->sock = TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_STREAM, 0));
    setOptions();
}

int _SocksSocketImpl::connect() {
    if(TEMP_FAILURE_RETRY(::connect(sock, (struct sockaddr *)&mSockAddr, sizeof(mSockAddr))) < 0) {
        ::close(sock);
        return -1;
    }

    struct sockaddr_in local_address;
    memset(&local_address,0,sizeof(struct sockaddr_in));

    socklen_t length = 0;
    int ret = getpeername(sock, ( struct sockaddr* )&local_address, &length);
    
    while(ntohs(local_address.sin_port ) == 0) {
        usleep(30*1000);
        memset(&local_address,0,sizeof(struct sockaddr_in));
        getpeername(sock, ( struct sockaddr* )&local_address, &length);
    }

    return ret;
}
    
};
