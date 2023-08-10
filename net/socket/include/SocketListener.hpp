#ifndef __OBOTCHA_SOCKET_LISTENER_HPP__
#define __OBOTCHA_SOCKET_LISTENER_HPP__

#include "Object.hpp"

#include "Socket.hpp"
#include "Net.hpp"

namespace obotcha {

DECLARE_CLASS(SocketListener) {
public:
    virtual void onSocketMessage(st(Net)::Event,Socket,ByteArray) = 0;
};

}
#endif
