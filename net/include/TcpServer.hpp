#ifndef __OBOTCHA_TCP_SERVER_HPP__
#define __OBOTCHA_TCP_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>

#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"
#include "EPollFileObserver.hpp"
#include "Atomic.hpp"

namespace obotcha {

class _WebSocketServer;
class _TcpServer;

DECLARE_SIMPLE_CLASS(TcpServerSocket) {
public:
    friend class _TcpServer;

    _TcpServerSocket(int fd);
    
    int send(ByteArray);
    
    int getFd();

private:
    void enableSend();
    Mutex mMutex;
    Atomic<bool> isCacheEmpty;
    Condition mCondition;
    int mFd;
};


DECLARE_SIMPLE_CLASS(TcpServer) EXTENDS(EPollFileObserverListener){
    
public:
    friend class _WebSocketServer;

    _TcpServer(int port,SocketListener l = nullptr);

    _TcpServer(String ip,int port,SocketListener l,int connect=1024);

    _TcpServer(String ip,int port);

    void deMonitor(int fd);

    int start();

    void release();

    ~_TcpServer();

    TcpServerSocket getSocket(int);

private:

    int connect();

    int onEvent(int fd,uint32_t events,ByteArray);

    SocketListener mListener;

    struct sockaddr_in serverAddr;

    int sock;

    EPollFileObserver mObserver;

    int mConnectionNum;
    
    Mutex mSocketMapMutex;
    HashMap<int,sp<_TcpServerSocket>> mSocketMap;
};

}
#endif
