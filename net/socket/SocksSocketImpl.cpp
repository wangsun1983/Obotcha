#include <fcntl.h>

#include "SocksSocketImpl.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "OStdReturnValue.hpp"

namespace obotcha {

// socket
_SocksSocketImpl::_SocksSocketImpl(InetAddress address, SocketOption option)
    : _SocketImpl(address, option) {
    mSock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(address->getSockAddress()->family(), 
                                SOCK_STREAM, 
                                0)));
    
    if(mSock->getFd() < 0) {
        LOG(ERROR)<<"SocksSocket open fd failed,reason is "<<strerror(errno);
        Trigger(InitializeException,"create socket fd failed")
    }

    //setOptions();
    if(option != nullptr) {
        option->update(mSock);
    }
}

int _SocksSocketImpl::connect() {
    // check whether fd is async
    if ((fcntl(mSock->getFd(), F_GETFL, 0) & O_NONBLOCK) != 0) {
        LOG(ERROR) << "Socket fd is async,connect will fail!!!";
        return -1;
    }

    socklen_t sock_length = 0;
    struct sockaddr *sock_addr = nullptr;
    FetchRet(sock_length,sock_addr) = mAddress->getSockAddress()->get();

    if (TEMP_FAILURE_RETRY(::connect(mSock->getFd(),sock_addr,sock_length)) < 0) {
        printf("connect error is %s \n",strerror(errno));
        mSock->close();
        return -1;
    }

    while (1) {
        SockAddress sockAddr = createSockAddress(mAddress->getFamily());
        struct sockaddr *addr = nullptr;
        socklen_t size = 0;

        FetchRet(size,addr) = sockAddr->get();

        if(getpeername(mSock->getFd(),addr,&size) == 0 && ntohs(sockAddr->port() != 0)) {
            break;
        }
        usleep(30 * 1000);
    }

    return 0;
}

}; // namespace obotcha
