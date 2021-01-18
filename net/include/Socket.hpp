#ifndef __OBOTCHA_SOCKET_HPP__
#define __OBOTCHA_SOCKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Socket) {
public:
    _Socket(int);

    int send(ByteArray,int);
    int send(ByteArray);

    int getFd();
    
private:
    int mFd;    
};

}

#endif