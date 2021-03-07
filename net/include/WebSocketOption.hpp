#ifndef __OBOTCHA_WEBSOCKET_OPTION_HPP__
#define __OBOTCHA_WEBSOCKET_OPTION_HPP__

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

DECLARE_SIMPLE_CLASS(WebSocketOption) {
public:
    _WebSocketOption();
    _WebSocketOption* setRecvTimeout(int);
    _WebSocketOption* setSendTimeout(int);
    _WebSocketOption* setConnectionNum(int);

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
