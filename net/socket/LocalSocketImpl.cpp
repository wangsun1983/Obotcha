#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <memory.h>
#include <netinet/in.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include "Exception.hpp"
#include "FileDescriptor.hpp"
#include "InitializeException.hpp"
#include "LocalSocketImpl.hpp"

namespace obotcha {

_LocalSocketImpl::_LocalSocketImpl(InetAddress address, SocketOption option)
    : _SocketImpl(address, option) {
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, address->getAddress()->toChars());

    // if client setReUseAddr,connect will failed!!
    if (option != nullptr && option->getReUseAddr() == st(SocketOption)::On) {
        unlink(address->getAddress()->toChars());
    }

    sock = createFileDescriptor(
        TEMP_FAILURE_RETRY(socket(AF_UNIX, SOCK_STREAM, 0)));
    if (sock->getFd() < 0) {
        Trigger(InitializeException, "Socket create failed");
    }
    setOptions();
}

int _LocalSocketImpl::connect() {
    if (::connect(sock->getFd(), (struct sockaddr *)&serverAddr,
                  sizeof(serverAddr)) < 0) {
        return -errno;
    }

    while (1) {
        struct sockaddr_in local_address;
        memset(&local_address, 0, sizeof(struct sockaddr_in));
        socklen_t length = 0;
        int ret = getpeername(sock->getFd(), (struct sockaddr *)&local_address,
                              &length);
        if (ntohs(local_address.sin_port) == 0) {
            break;
        }
        usleep(30 * 1000);
    }

    return 0;
}

} // namespace obotcha
