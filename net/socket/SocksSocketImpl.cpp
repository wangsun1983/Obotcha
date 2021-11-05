#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <memory.h>
#include <netinet/in.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "Error.hpp"
#include "FileDescriptor.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "SocksSocketImpl.hpp"
#include "System.hpp"

namespace obotcha {

// socket
_SocksSocketImpl::_SocksSocketImpl(InetAddress address, SocketOption option)
    : _SocketImpl(address, option) {
    switch(address->getType()) {
        case st(InetAddress)::IPV4: {
            mSockAddr.sin_family = PF_INET;
            mSockAddr.sin_port = htons(address->getPort());
            if (address->getAddress() != nullptr) {
                mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
            } else {
                mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
            }

            this->sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_STREAM, 0)));
        }
        break;

        case st(InetAddress)::IPV6: {
            mSockAddrV6.sin6_family = PF_INET6;
            mSockAddrV6.sin6_port = htons(address->getPort());
            if (address->getAddress() != nullptr) {
                //mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
                inet_pton(AF_INET6, address->getAddress()->toChars(), &mSockAddrV6.sin6_addr);
            } else {
                mSockAddrV6.sin6_addr = in6addr_any;
            }

            this->sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(AF_INET6, SOCK_STREAM, 0)));
        
        }
        break;
    }

    
    setOptions();
}

int _SocksSocketImpl::connect() {
    // check whether fd is async
    if ((fcntl(sock->getFd(), F_GETFL, 0) & O_NONBLOCK) != 0) {
        LOG(ERROR) << "socket fd is async,connect will fail!!!";
    }

    if (TEMP_FAILURE_RETRY(::connect(sock->getFd(),
                                     (struct sockaddr *)&mSockAddr,
                                     sizeof(mSockAddr))) < 0) {
        sock->close();

        return -1;
    }

    while (1) {
        struct sockaddr_in local_address;
        memset(&local_address, 0, sizeof(struct sockaddr_in));
        socklen_t length = 0;
        int ret = getpeername(sock->getFd(), (struct sockaddr *)&local_address,
                              &length);
        if (ntohs(local_address.sin_port) == 0) {
            break;
        }
        usleep(30 * 1000);
    }

    return 0;
}

}; // namespace obotcha
