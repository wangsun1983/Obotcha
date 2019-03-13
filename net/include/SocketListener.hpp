#ifndef __SOCKET_LISTENER_HPP__
#define __SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketPacket.hpp"

DECLARE_SIMPLE_CLASS(SocketListener) {
public:
    virtual void onAccept(int fd,SocketPacket pack) = 0;

    virtual void onDisconnect(int fd) = 0;

    virtual void onConnect(int fd) = 0;
};
#endif
