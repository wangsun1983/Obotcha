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
    struct sockaddr *addr = nullptr;
    socklen_t length = 0;

    FetchRet(length,addr) = this->address->getSockAddress()->get();
    if(::bind(sock->getFd(),addr,length) < 0) {
        return -errno;
    }

    int connectNum = DefaultConnectNum;
    if (option != nullptr) {
        connectNum = option->getConnectionNum();
    }

    if (listen(sock->getFd(), connectNum) < 0) {
        return -errno;
    }

    return 0;
}

Socket _ServerSocketImpl::accept() {
    SockAddress client = createSockAddress(this->address->getFamily());
    struct sockaddr *client_address = nullptr;
    socklen_t client_length = 0;
    FetchRet(client_length,client_address) = client->get();
    
    int clientfd = ::accept(sock->getFd(), (struct sockaddr *)client_address,
                            &client_length);
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
