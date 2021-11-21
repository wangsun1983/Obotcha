#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <memory.h>
#include <netinet/in.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include "DatagramSocketImpl.hpp"
#include "FileDescriptor.hpp"
#include "InitializeException.hpp"
#include "Socket.hpp"
#include "Inet6Address.hpp"
#include "Inet4Address.hpp"
#include "SocketBuilder.hpp"

namespace obotcha {

_DatagramSocketImpl::_DatagramSocketImpl():_SocketImpl(){

}

_DatagramSocketImpl::_DatagramSocketImpl(InetAddress address,
                                         SocketOption option)
    : _SocketImpl(address, option) {

    switch(address->getType()) {
        case st(InetAddress)::IPV4: {
            mSockAddr.sin_family = AF_INET;
            mSockAddr.sin_port = htons(address->getPort());

            if (address->getAddress() != nullptr) {
                mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
            } else {
                mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
            }

            sock = createFileDescriptor(
                TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)));
        }
        break;

        case st(InetAddress)::IPV6: {
            mSockAddrV6.sin6_family = AF_INET6;
            mSockAddrV6.sin6_port = htons(address->getPort());
            if (address->getAddress() != nullptr) {
                //mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
                inet_pton(AF_INET6, address->getAddress()->toChars(), &mSockAddrV6.sin6_addr);
            } else {
                mSockAddrV6.sin6_addr = in6addr_any;
            }

            this->sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)));
        }
        break;
    }

    
    if (sock->getFd() < 0) {
        Trigger(InitializeException, "Datagram Socket create failed");
    }

    setOptions();
}

Socket _DatagramSocketImpl::receiveFrom(ByteArray buff) {
    Socket newClient = nullptr;
    int length = -1;
    struct sockaddr_in client_address;
    socklen_t client_addrLength = sizeof(struct sockaddr_in);
    
    struct sockaddr_in6 client_address_v6;
    socklen_t client_addrLength_v6 = sizeof(struct sockaddr_in6);

    switch(this->address->getType()) {
        case st(InetAddress)::IPV4: {
            printf("recv ipv4 \n");
            length = recvfrom(
                sock->getFd(), buff->toValue(), buff->size(), 0,
                (sockaddr *)&client_address, &client_addrLength);

            if(length > 0) {
                auto addr = createInet4Address(createString(
                        inet_ntoa(client_address.sin_addr)),
                        ntohs(client_address.sin_port));

                DatagramSocketImpl impl = createDatagramSocketImpl();
                impl->address = addr;
                memcpy(&impl->mSockAddr,&client_address,client_addrLength);

                impl->sock = sock;
                newClient = createSocket();
                newClient->setSockImpl(impl);
                newClient->setType(st(Socket)::Udp);

                printf("addr is %s,port is %d,fd is %d \n",inet_ntoa(client_address.sin_addr),client_address.sin_port,sock->getFd());
                buff->quickShrink(length);
            }
        }
        break;

        case st(InetAddress)::IPV6: {
            printf("recv ipv6 \n");
            length = recvfrom(
                sock->getFd(), buff->toValue(), buff->size(), 0,
                (sockaddr *)&client_address_v6, &client_addrLength_v6);

            if (length > 0) {
                char buf_ip[128];
                memset(buf_ip,0,128);
                inet_ntop(AF_INET6, &client_address_v6.sin6_addr, buf_ip, sizeof(buf_ip));
                printf("i recv ip is %s \n",buf_ip);
                Inet6Address inet6Addr = createInet6Address(
                    createString(buf_ip),ntohs(client_address_v6.sin6_port));

                DatagramSocketImpl impl = createDatagramSocketImpl();
                impl->address = inet6Addr;
                memcpy(&impl->mSockAddrV6,&client_address_v6,client_addrLength_v6);

                impl->sock = sock;
                newClient = createSocket();
                newClient->setSockImpl(impl);
                newClient->setType(st(Socket)::Udp);
                buff->quickShrink(length);
            }
        }
        break;
    }

    return newClient;
}

int _DatagramSocketImpl::connect() {
    // return ::connect(sock->getFd(),(struct
    // sockaddr*)&mSockAddr,sizeof(mSockAddr));
    return 0;
}

int _DatagramSocketImpl::bind() {
    switch(this->address->getType()) {
        case st(InetAddress)::IPV4: {
            return ::bind(sock->getFd(), (struct sockaddr *)&mSockAddr,
                  sizeof(mSockAddr));
        }

        case st(InetAddress)::IPV6: {
            return ::bind(sock->getFd(), (struct sockaddr *)&mSockAddrV6,
                  sizeof(mSockAddrV6));
        }
    }

    return -1;
}

int _DatagramSocketImpl::write(ByteArray data,int start,int length) {
    printf("_DatagramSocketImpl write start \n");
    struct sockaddr * addr = nullptr;
    int addrlen = 0;

    switch(this->address->getType()) {
        case st(InetAddress)::IPV4: {
            addr = (sockaddr *)&mSockAddr;
            addrlen = sizeof(mSockAddr);
        }
        break;

        case st(InetAddress)::IPV6: {
            addr = (sockaddr *)&mSockAddrV6;
            addrlen = sizeof(mSockAddrV6);
        }
        break;
    }
    printf("_DatagramSocketImpl write trace1 \n");
    if(start + length > data->size()) {
        //TODO
        return -1;
    }
    printf("_DatagramSocketImpl write trace2,addr is %s ,port is %d \n",inet_ntoa(mSockAddr.sin_addr),mSockAddr.sin_port);
    int size = (length == -1?data->size() - start:length);
    int ret =  ::sendto(sock->getFd(), data->toValue() + start, size, 0,addr, addrlen);
    printf("_DatagramSocketImpl write trace3 ret is %d \n",size);
    return ret;
}

} // namespace obotcha