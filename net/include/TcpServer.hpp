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

DECLARE_SIMPLE_CLASS(TcpSocketObserver) EXTENDS(EPollFileObserverListener){
public:
    _TcpSocketObserver(SocketListener,int,EPollFileObserver o);
    int onEvent(int fd,uint32_t events,ByteArray);

private:
    SocketListener mListener;
    EPollFileObserver mObserver;
    int mSock;
};

DECLARE_SIMPLE_CLASS(TcpServer) {
    
public:
    friend class _WebSocketServer;

    _TcpServer(int port,SocketListener l);

    _TcpServer(String ip,int port,SocketListener l,int connect=1024);

    int start();

    void release();

    int send(int fd,ByteArray data);

    int removeClientFd(int fd);

    int addClientFd(int fd);

    int getStatus();

    ~_TcpServer();

private:

    int connect();

    SocketListener mListener;

    struct sockaddr_in serverAddr;

    int sock;

    AtomicInteger mStatus;

    EPollFileObserver mObserver;

    TcpSocketObserver mLocalListener;

    int mConnectionNum;
};

}
#endif
