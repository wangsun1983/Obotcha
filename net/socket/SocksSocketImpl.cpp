#include <fcntl.h>

#include "SocksSocketImpl.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "OStdReturnValue.hpp"
#include "System.hpp"

namespace obotcha {

// socket
_SocksSocketImpl::_SocksSocketImpl(InetAddress address, SocketOption option)
    : _SocketImpl(address, option) {
    mSock = FileDescriptor::New(TEMP_FAILURE_RETRY(socket(address->getSockAddress()->family(), 
                                SOCK_STREAM, 
                                0)));
    
    if(mSock->getFd() < 0) {
        LOG(ERROR)<<"SocksSocket open fd failed,reason is "<<strerror(errno);
        Trigger(InitializeException,"create socket fd failed")
    }

    if(option != nullptr) {
        option->update(mSock);
    }
}

int _SocksSocketImpl::connect() {
    // check whether fd is async
    int fd = mSock->getFd();
    bool isAsync = mSock->isAsync();

    if (isAsync) {
        LOG(ERROR) << "Socket fd is async,connect will fail!!!";
        //set as block io before connect
        //if we use libco,this library override sock function
        //and change sock as async directly
        mSock->setAsync(false);
    }

    int connectTimeout = (mOption == nullptr)?-1:mOption->getConnectTimeout();
    if(connectTimeout != -1)  {
        timeval tv;
        tv.tv_sec = connectTimeout / 1000;
        tv.tv_usec = (connectTimeout % 1000) * 1000;
        ::setsockopt(fd,SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    }

    FetchRet(sock_length,sock_addr) = mAddress->getSockAddress()->get();
    if (TEMP_FAILURE_RETRY(::connect(fd,sock_addr,sock_length)) < 0) {
        mSock->close();
        return -1;
    }

    while(true) {
        SockAddress sockAddr = SockAddress::New(mAddress->getFamily());
        FetchRet(size,addr) = sockAddr->get();
        if(getpeername(fd,addr,(socklen_t *)&size) == 0) {
            break;
        }
        st(System)::Sleep(30);
    }

    int sendTimeout = (mOption == nullptr)?0:mOption->getSndTimeout();
    timeval send_tv;
    if(sendTimeout != 0) {
        send_tv.tv_sec = sendTimeout / 1000;
        send_tv.tv_usec = (sendTimeout % 1000) * 1000;
    } else {
        send_tv.tv_sec = 0;
        send_tv.tv_usec = 0;
    }
    ::setsockopt(mSock->getFd(),SOL_SOCKET, SO_SNDTIMEO, &send_tv, sizeof(send_tv));

    int recvTimeout = (mOption == nullptr)?0:mOption->getRcvTimeout();
    if(recvTimeout != 0) {
        timeval tv;
        tv.tv_sec = recvTimeout / 1000;
        tv.tv_usec = (recvTimeout % 1000) * 1000;
        ::setsockopt(mSock->getFd(),SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    }
    
    if(isAsync) {
        mSock->setAsync(true);
    }
    
    return 0;
}

}; // namespace obotcha
