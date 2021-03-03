#ifndef __OBOTCHA_SOCKET_LISTENER_HPP__
#define __OBOTCHA_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "Socket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketListener) {
public:
    //virtual void onAcceptTcp(int fd,ByteArray pack) {};
    virtual void onDataReceived(Socket s,ByteArray pack) = 0;

    virtual void onDisconnect(Socket s) = 0;

    virtual void onConnect(Socket s) = 0;
};

}
#endif
