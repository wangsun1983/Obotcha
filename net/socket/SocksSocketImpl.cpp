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
#include "FileDescriptor.hpp"
#include "Log.hpp"

namespace obotcha {

//socket
_SocksSocketImpl::_SocksSocketImpl(InetAddress address,SocketOption option):_SocketImpl(address,option){
    mSockAddr.sin_family = PF_INET;
    mSockAddr.sin_port = htons(address->getPort());
    mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
    
    this->sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_STREAM, 0)));
    setOptions();
}

int _SocksSocketImpl::connect() {
    //check whether fd is async
    if((fcntl(sock->getFd(), F_GETFL, 0)&O_NONBLOCK) != 0) {
        LOG(ERROR)<<"socket fd is async,connect will fail!!!";
    }

    if(TEMP_FAILURE_RETRY(::connect(sock->getFd(), (struct sockaddr *)&mSockAddr, sizeof(mSockAddr))) < 0) {
        sock->close();

        return -1;
    }

    while(1) {
        struct sockaddr_in local_address;
        memset(&local_address,0,sizeof(struct sockaddr_in));
        socklen_t length = 0;
        int ret = getpeername(sock->getFd(), ( struct sockaddr* )&local_address, &length);
        if(ntohs(local_address.sin_port ) == 0) {
            break;
        }
        usleep(30*1000);
    }

    return 0;
}
    
};
