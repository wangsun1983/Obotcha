#ifndef __WEB_SOCKET_LISTENER_HPP__
#define __WEB_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketListener) {
public:

    virtual int onMessage(int fd,String message) = 0;

    virtual int onConnect(int fd) = 0;

    virtual int onDisconnect(int fd) = 0;

    virtual int onPong(int fd);

    virtual int onPing(int fd);
};

}
#endif
