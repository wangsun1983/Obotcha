#ifndef __OBOTCHA_SOCKET_MONITOR_HPP__
#define __OBOTCHA_SOCKET_MONITOR_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Socket.hpp"
#include "EPollFileObserver.hpp"
#include "SocketListener.hpp"
#include "ServerSocket.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(SocketMonitor) {
public:
    _SocketMonitor();

    int bind(Socket,SocketListener);
    int bind(ServerSocket,SocketListener);
    int bind(int,SocketListener);
    
    int remove(int);

    void release();
    //add lambda
    template< class Function, class... Args >
    int bindConnect(Socket,Function&& f, Args&&... args) {

    }

    template< class Function, class... Args >
    int bindData(Socket,Function&& f, Args&&... args) {
        
    }

    template< class Function, class... Args >
    int bindDisconnect(Socket,Function&& f, Args&&... args) {
        
    }
    
private:
    
    EPollFileObserver mPoll;
};

}

#endif