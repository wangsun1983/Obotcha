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
#include "IllegalArgumentException.hpp"
#include "Log.hpp"

namespace obotcha {

_DatagramSocketImpl::_DatagramSocketImpl():_SocketImpl(){

}

_DatagramSocketImpl::_DatagramSocketImpl(InetAddress address,
                                         SocketOption option)
    : _SocketImpl(address, option) {
    
    sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(address->getSockAddress()->family(), 
                                SOCK_DGRAM,
                                IPPROTO_UDP)));

    // switch(address->getFamily()) {
    //     case st(InetAddress)::IPV4: {
    //         sock = createFileDescriptor(
    //             TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)));
    //     }
    //     break;

    //     case st(InetAddress)::IPV6: {
    //         //this->sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(AF_INET6, SOCK_STREAM, 0)));
    //         sock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)));
    //     }
    //     break;

    //     default:
    //         LOG(ERROR)<<"create DatagramSocketImpl socket type unknown";
    //     break;
    // }

    
    if (sock->getFd() < 0) {
        Trigger(InitializeException, "Datagram Socket create failed");
    }

    setOptions();
}

Socket _DatagramSocketImpl::recvDatagram(ByteArray buff) {
    Socket newClient = createSocket();
    int length = -1;
    DatagramSocketImpl impl = createDatagramSocketImpl();

    SockAddress client = createSockAddress(address->getFamily());
    struct sockaddr *client_addr = nullptr;
    socklen_t client_len = 0;

    FetchRet(client_len,client_addr) = client->get();
    length = recvfrom(sock->getFd(), buff->toValue(), buff->size(), 0, client_addr, &client_len);
    
    impl->address = client->toInetAddress();
    impl->sock = sock;

    if(length > 0) {
        newClient = createSocket(st(Socket)::Udp,impl);
        //newClient->setSockImpl(impl);
        //newClient->setProtocol(st(Socket)::Udp);
        buff->quickShrink(length);
        return newClient;
    }

    return nullptr;
}

int _DatagramSocketImpl::connect() {
    //UDP do not need to do connect
    return 0;
}

int _DatagramSocketImpl::bind() {

    struct sockaddr *addr = nullptr;
    socklen_t len = 0;
    FetchRet(len,addr) = address->getSockAddress()->get();

    return ::bind(sock->getFd(),addr,len);

    // switch(this->address->getFamily()) {
    //     case st(InetAddress)::IPV4: {
    //         return ::bind(sock->getFd(), (struct sockaddr *)&mSockAddr,
    //               sizeof(mSockAddr));
    //     }

    //     case st(InetAddress)::IPV6: {
    //         return ::bind(sock->getFd(), (struct sockaddr *)&mSockAddrV6,
    //               sizeof(mSockAddrV6));
    //     }
    // }
    // Trigger(IllegalArgumentException,"DatagramSocket must be IPV4 or IPV6");
}

int _DatagramSocketImpl::write(ByteArray data,int start,int length) {

    //struct sockaddr * addr = nullptr;
    //int addrlen = 0;
    if(start + length > data->size()) {
        Trigger(IllegalArgumentException,"DatagramSocket write size too large");
    }

    // switch(this->address->getFamily()) {
    //     case st(InetAddress)::IPV4: {
    //         addr = (sockaddr *)&mSockAddr;
    //         addrlen = sizeof(mSockAddr);
    //     }
    //     break;

    //     case st(InetAddress)::IPV6: {
    //         addr = (sockaddr *)&mSockAddrV6;
    //         addrlen = sizeof(mSockAddrV6);
    //     }
    //     break;
    // }
    
    struct sockaddr * addr = nullptr;
    socklen_t addrlen = 0;
    FetchRet(addrlen,addr) = address->getSockAddress()->get();

    int size = (length == -1?data->size() - start:length);
    return ::sendto(sock->getFd(), data->toValue() + start, size, 0,addr, addrlen);
}

} // namespace obotcha