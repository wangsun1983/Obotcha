#include "SocketImpl.hpp"

namespace obotcha {

_SocketImpl::_SocketImpl(int fd) {
    sock = fd;
}

_SocketImpl::_SocketImpl(InetAddress address,SocketOption option) {
    this->address = address;
    this->option = option;
}

int _SocketImpl::close() {
    if(sock != -1) {
        ::close(sock);
        sock = -1;
    }
    
    return 0;
}

int _SocketImpl::getFd() {
    return this->sock;
}

InetAddress _SocketImpl::getInetAddress() {
    return address;
}

void _SocketImpl::setInetAddress(InetAddress addr) {
    address = addr;
}

}
