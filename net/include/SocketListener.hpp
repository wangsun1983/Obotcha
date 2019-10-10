#ifndef __SOCKET_LISTENER_HPP__
#define __SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketListener) {
public:
    //virtual void onAcceptTcp(int fd,ByteArray pack) {};
    
    virtual void onAccept(int fd,String ip,int port,ByteArray pack) = 0;

    virtual void onDisconnect(int fd) = 0;

    virtual void onConnect(int fd,String ip,int port) = 0;

    virtual void onConnect(int fd,String domain) = 0;

    virtual void onTimeout() = 0;
};

}
#endif
