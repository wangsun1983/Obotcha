#ifndef __OBOTCHA_SOCKET_LISTENER_HPP__
#define __OBOTCHA_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "Socket.hpp"
#include "NetEvent.hpp"

namespace obotcha {

DECLARE_CLASS(SocketListener) IMPLEMENTS(NetEvent){
public:
    virtual void onSocketMessage(int,Socket,ByteArray) = 0;
};

}
#endif
