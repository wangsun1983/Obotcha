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

namespace obotcha {

_DatagramSocketImpl::_DatagramSocketImpl(InetAddress address,
                                         SocketOption option)
    : _SocketImpl(address, option) {
    mSockAddr.sin_family = AF_INET;
    mSockAddr.sin_port = htons(address->getPort());

    if (address->getAddress() != nullptr) {
        mSockAddr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
    } else {
        mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    sock = createFileDescriptor(
        TEMP_FAILURE_RETRY(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)));
    if (sock->getFd() < 0) {
        Trigger(InitializeException, "Datagram Socket create failed");
    }

    setOptions();
}

int _DatagramSocketImpl::connect() {
    // return ::connect(sock->getFd(),(struct
    // sockaddr*)&mSockAddr,sizeof(mSockAddr));
    return 0;
}

int _DatagramSocketImpl::bind() {
    return ::bind(sock->getFd(), (struct sockaddr *)&mSockAddr,
                  sizeof(mSockAddr));
}

} // namespace obotcha