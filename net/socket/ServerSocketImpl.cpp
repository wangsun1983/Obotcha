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
}

int _ServerSocketImpl::bind() {
    switch(this->address->getFamily()) {
        case st(InetAddress)::IPV4: {
            if (::bind(sock->getFd(), (struct sockaddr *)&mSockAddr,sizeof(sockaddr)) < 0) {
                return -NetBindFail;
            }
        }
        break;

        case st(InetAddress)::IPV6: {
            if (::bind(sock->getFd(), (struct sockaddr *)&mSockAddrV6,sizeof(sockaddr_in6)) < 0) {
                return -NetBindFail;
            }
        }
        break;
    }
    
    int connectNum = DefaultConnectNum;
    if (option != nullptr) {
        connectNum = option->getConnectionNum();
    }

    if (listen(sock->getFd(), connectNum) < 0) {
        return -NetListenFail;
    }

    return 0;
}

Socket _ServerSocketImpl::accept() {
    
    struct sockaddr_in *client_address;
    socklen_t client_addrLength = 0;//sizeof(struct sockaddr_in);

    struct sockaddr_in ipv4_addr;
    struct sockaddr_in6 ipv6_addr;

    switch(this->address->getFamily()) {
        case st(InetAddress)::IPV4: {
            client_address = &ipv4_addr;
            client_addrLength = sizeof(struct sockaddr_in);
        }
        break;

        case st(InetAddress)::IPV6: {
            client_address = (struct sockaddr_in *)&ipv6_addr;
            client_addrLength = sizeof(struct sockaddr_in6);
        }
    }
    
    int clientfd = ::accept(sock->getFd(), (struct sockaddr *)client_address,
                            &client_addrLength);
    if (clientfd > 0) {
        switch(this->address->getFamily()) {
            case st(InetAddress)::IPV4: {
                InetAddress clientAddr =
                    createInetAddress(createString(inet_ntoa(ipv4_addr.sin_addr)),
                                    ntohs(ipv4_addr.sin_port));

                return createSocketBuilder()
                    ->setAddress(clientAddr)
                    ->setFileDescriptor(createFileDescriptor(clientfd))
                    ->newSocket();
            }
            break;

            case st(InetAddress)::IPV6: {
                char buf[256];
                memset(buf,0,256);
                struct sockaddr_in6 *client_address_ipv6 = (struct sockaddr_in6 *)&client_address;
                inet_ntop(AF_INET6, &ipv6_addr.sin6_addr, buf, sizeof(buf));
                String ip = createString(buf);

                Inet6Address clientAddr = createInet6Address(ip,ipv6_addr.sin6_port);

                return createSocketBuilder()
                    ->setAddress(clientAddr)
                    ->setFileDescriptor(createFileDescriptor(clientfd))
                    ->newSocket();
            }
            break;

            default:
            LOG(ERROR)<<"accept address error!!!!,type is"<<this->address->getFamily();
            break;
        }
    } else {
        LOG(ERROR)<<"accept failed error is" <<strerror(errno);
    }

    return nullptr;
}

} // namespace obotcha
