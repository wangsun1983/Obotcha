#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "SocketResponser.hpp"

namespace obotcha {

_SocketResponser::_SocketResponser(int fd,String ip,int port) {
    mFd = fd;
    mIp = ip;
    mPort = port;
}

_SocketResponser::_SocketResponser(String domain,int fd) {
    mFd = fd;
    mDomain = domain;
}

int _SocketResponser::send(ByteArray packet) {
    return write(mFd,packet->toValue(),packet->size());
}

int _SocketResponser::getFd() {
    return mFd;
}

String _SocketResponser::getIp() {
    return mIp;
}

int _SocketResponser::getPort() {
    return mPort;
}

String _SocketResponser::getDomain() {
    return mDomain;
}

}

