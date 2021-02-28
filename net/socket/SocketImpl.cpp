#include "SocketImpl.hpp"

namespace obotcha {

_SocketImpl::_SocketImpl(InetAddress address,int port,SocketOption option) {
    this->address = address;
    this->port = port;
    this->option = option;
}

int _SocketImpl::close() {
    return ::close(sock);
}

int _SocketImpl::getFd() {
    return this->sock;
}

}
