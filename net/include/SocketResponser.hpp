#ifndef __OBOTCHA_SOCKET_RESPONSER_HPP__
#define __OBOTCHA_SOCKET_RESPONSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketResponser) {
public:
    _SocketResponser(int fd);

    int send(ByteArray);
    
    int getFd();
private:

    int mFd;
};

}
#endif
