#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "ServerSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "Inet6Address.hpp"
#include "Log.hpp"

namespace obotcha {

int _ServerSocketImpl::DefaultConnectNum = 16;

_ServerSocketImpl::_ServerSocketImpl(InetAddress address, SocketOption option)
    : _SocketImpl(address, option), _SocksSocketImpl(address, option) {

    // if client setReUseAddr,connect will failed!!
    if (option != nullptr
        && address->getFamily() == st(InetAddress)::LOCAL
        && option->getReUseAddr() == st(SocketOption)::On) {
        unlink(address->getAddress()->toChars());
    }
}

int _ServerSocketImpl::bind() {
    printf("ServerSocketImpl bind \n");
    FetchRet(length,addr) = this->mAddress->getSockAddress()->get();
    if(::bind(mSock->getFd(),addr,length) < 0) {
        return -errno;
    }

    int waitAcceptQueueSize = (mOption == nullptr)?
                            st(SocketOption)::DefaultWaitAcceptQueueSize
                            :mOption->getWaitAcceptQueueSize();
 
    if (listen(mSock->getFd(), waitAcceptQueueSize) < 0) {
        return -errno;
    }
    printf("ServerSocketImpl bind end\n");
    return 0;
}

Socket _ServerSocketImpl::accept() {
    SockAddress client = createSockAddress(this->mAddress->getFamily());
    FetchRet(client_length,client_address) = client->get();
    
    int clientfd = ::accept(mSock->getFd(), (struct sockaddr *)client_address,
                            (socklen_t *)&client_length);
    if (clientfd > 0) {
        InetAddress address = client->toInetAddress();
        return createSocketBuilder()
                    ->setAddress(address)
                    ->setFileDescriptor(createFileDescriptor(clientfd))
                    ->newSocket();
    } else {
        LOG(ERROR)<<"accept failed error is" <<strerror(errno);
    }

    return nullptr;
}

} // namespace obotcha
