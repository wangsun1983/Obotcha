#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "SocketResponser.hpp"

namespace obotcha {

_SocketResponser::_SocketResponser(int fd) {
    mFd = fd;
}

int _SocketResponser::send(ByteArray packet) {
    return write(mFd,packet->toValue(),packet->size());
}
    
int _SocketResponser::getFd() {
    return mFd;
}

}

