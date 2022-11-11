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
#include "Log.hpp"
#include "OStdReturnValue.hpp"
#include "Log.hpp"

namespace obotcha {

// socket
_SocksSocketImpl::_SocksSocketImpl(InetAddress address, SocketOption option)
    : _SocketImpl(address, option) {
    sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(address->getSockAddress()->family(), 
                                SOCK_STREAM, 
                                0)));
    
    if(sock->getFd() < 0) {
        LOG(ERROR)<<"SocksSocket open fd failed,reason is "<<strerror(errno);
        Trigger(InitializeException,"create socket fd failed")
    }

    //setOptions();
    if(option != nullptr) {
        option->update(sock);
    }
}

int _SocksSocketImpl::connect() {
    // check whether fd is async
    if ((fcntl(sock->getFd(), F_GETFL, 0) & O_NONBLOCK) != 0) {
        LOG(ERROR) << "Socket fd is async,connect will fail!!!";
        return -1;
    }

    socklen_t sock_length = 0;
    struct sockaddr *sock_addr = nullptr;
    FetchRet(sock_length,sock_addr) = address->getSockAddress()->get();

    if (TEMP_FAILURE_RETRY(::connect(sock->getFd(),sock_addr,sock_length)) < 0) {
        printf("connect error is %s \n",strerror(errno));
        sock->close();
        return -1;
    }

    while (1) {
        SockAddress sockAddr = createSockAddress(address->getFamily());
        struct sockaddr *addr = nullptr;
        socklen_t size = 0;

        FetchRet(size,addr) = sockAddr->get();

        if(getpeername(sock->getFd(),addr,&size) == 0 && ntohs(sockAddr->port() != 0)) {
            break;
        }
        usleep(30 * 1000);
    }

    return 0;
}

}; // namespace obotcha
