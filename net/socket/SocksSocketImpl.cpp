#include <fcntl.h>

#include "SocksSocketImpl.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "OStdReturnValue.hpp"
#include "InfiniteLoop.hpp"

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

    int connectTimeout = (mOption == nullptr)?0:mOption->getConnectTimeout();
    if(connectTimeout != -1)  {
        timeval tv;
        tv.tv_sec = connectTimeout / 1000;
        tv.tv_usec = (connectTimeout % 1000) * 1000;
        ::setsockopt(mSock->getFd(),SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    }

    FetchRet(sock_length,sock_addr) = mAddress->getSockAddress()->get();
    if (TEMP_FAILURE_RETRY(::connect(mSock->getFd(),sock_addr,sock_length)) < 0) {
        mSock->close();
        return -1;
    }

    InfiniteLoop {
        SockAddress sockAddr = createSockAddress(mAddress->getFamily());
        FetchRet(size,addr) = sockAddr->get();
        if(getpeername(mSock->getFd(),addr,(socklen_t *)&size) == 0 && ntohs(sockAddr->port() != 0)) {
            break;
        }
        usleep(30 * 1000);
    }

    //reset sendTimeout
    if(connectTimeout != -1) {
        int sendTimeout = (mOption == nullptr)?0:mOption->getSndTimeout();
        timeval tv;
        tv.tv_sec = sendTimeout / 1000;
        tv.tv_usec = (sendTimeout % 1000) * 1000;
        ::setsockopt(mSock->getFd(),SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    }
    return 0;
}

}; // namespace obotcha
