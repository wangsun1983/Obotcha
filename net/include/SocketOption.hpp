#ifndef __OBOTCHA_SOCKET_OPTION_HPP__
#define __OBOTCHA_SOCKET_OPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketOption) {
public:
    _SocketOption();
    _SocketOption* setRecvTimeout(int);
    _SocketOption* setSendTimeout(int);
    _SocketOption* setConnectionNum(int);

    int getRcvTimeout();
    int getSendTimeout();
    int getConnectionNum();
private:
    int mRcvTimeout;
    int mSendTimeout;
    int mConnectNum;
};

}
#endif
