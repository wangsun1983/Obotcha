#ifndef __OBOTCHA_SOCKET_LISTENER_HPP__
#define __OBOTCHA_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "NetEvent.hpp"
#include "Socket.hpp"

namespace obotcha {

DECLARE_CLASS(SocketListener) IMPLEMENTS(NetEvent){
public:
    virtual void onSocketMessage(int,Socket,ByteArray) = 0;
};

}
#endif
