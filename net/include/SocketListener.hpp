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
    enum SocketEvent{
        Connect = 0,
        Message,
        Disconnect,
        InternalError,
    };

    virtual void onSocketMessage(int,Socket,ByteArray) = 0;
};

}
#endif
