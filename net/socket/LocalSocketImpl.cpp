#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <stddef.h>

#include "LocalSocketImpl.hpp"
#include "Exception.hpp"
#include "InitializeException.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

_LocalSocketImpl::_LocalSocketImpl(InetAddress address,SocketOption option):_SocketImpl(address,option) {
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, address->getAddress()->toChars()); 

    sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(AF_UNIX, SOCK_STREAM, 0)));
    if(sock->getFd() < 0) {
        Trigger(InitializeException,"Socket create failed");
    }
    setOptions();
}

int _LocalSocketImpl::connect() {
    if(::connect(sock->getFd(), (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        return -1;
    }

    struct sockaddr_in local_address;
    memset(&local_address,0,sizeof(struct sockaddr_in));

    socklen_t length = 0;
    int ret = getpeername(sock->getFd(), ( struct sockaddr* )&local_address, &length);
    
    while(ntohs( local_address.sin_port ) == 0) {
        usleep(30*1000);
        memset(&local_address,0,sizeof(struct sockaddr_in));
        getpeername(sock->getFd(), ( struct sockaddr* )&local_address, &length);
    }

    return 0;
}

}
