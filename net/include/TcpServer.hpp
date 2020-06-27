#ifndef __OBOTCHA_TCP_SERVER_HPP__
#define __OBOTCHA_TCP_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "AtomicInteger.hpp"
#include "Thread.hpp"
#include "EPollFileObserver.hpp"

namespace obotcha {

class _WebSocketServer;

DECLARE_SIMPLE_CLASS(LocalTcpSocketObserver) EXTENDS(EPollFileObserverListener){
public:
    _LocalTcpSocketObserver(SocketListener,int,EPollFileObserver o);
    int onEvent(int fd,uint32_t events,ByteArray);

private:
    SocketListener mListener;
    EPollFileObserver mObserver;
    int mSock;
};

DECLARE_SIMPLE_CLASS(TcpServer) {
    
public:
    friend class _WebSocketServer;

    _TcpServer(int port,SocketListener l = nullptr);

    _TcpServer(String ip,int port,SocketListener l,int connect=1024);

    _TcpServer(String ip,int port);

    int start();

    void release();

    int send(int fd,ByteArray data);

    ~_TcpServer();

private:

    int connect();

    SocketListener mListener;

    struct sockaddr_in serverAddr;

    int sock;

    AtomicInteger mStatus;

    EPollFileObserver mObserver;

    LocalTcpSocketObserver mLocalListener;

    int mConnectionNum;
};

}
#endif
