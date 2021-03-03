#ifndef __OBOTCHA_SOCKET_MONITOR_HPP__
#define __OBOTCHA_SOCKET_MONITOR_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Socket.hpp"
#include "EPollFileObserver.hpp"
#include "SocketListener.hpp"
#include "ServerSocket.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(SocketMonitor) {
public:
    _SocketMonitor();

    int bind(Socket,SocketListener);
    int bind(ServerSocket,SocketListener);
    int bind(int,SocketListener);
    
    int remove(Socket);

    void release();
    
private:
    
    EPollFileObserver mPoll;

    Mutex mMutex;
    HashMap<int,Socket> mSocks;

    int mServerSockFd;
};

}

#endif