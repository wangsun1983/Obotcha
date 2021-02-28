#ifndef __OBOTCHA_SOCKET_MONITOR_HPP__
#define __OBOTCHA_SOCKET_MONITOR_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Socket.hpp"
#include "EPollFileObserver.hpp"
#include "SocketListener.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(SocketMonitor) {
public:
    _SocketMonitor();

    int bind(Socket,SocketListener);
    
private:
    EPollFileObserver mPoll;
};

}

#endif