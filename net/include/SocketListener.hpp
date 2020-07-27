#ifndef __OBOTCHA_SOCKET_LISTENER_HPP__
#define __OBOTCHA_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "SocketResponser.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketListener) {
public:
    //virtual void onAcceptTcp(int fd,ByteArray pack) {};
    
    virtual void onDataReceived(SocketResponser r,ByteArray pack) = 0;

    virtual void onDisconnect(SocketResponser r) = 0;

    virtual void onConnect(SocketResponser r) = 0;

    virtual void onTimeout() = 0;
};

}
#endif
