#ifndef __OBOTCHA_LOCAL_SOCKET_SERVER_HPP__
#define __OBOTCHA_LOCAL_SOCKET_SERVER_HPP__

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

#define gDefaultLocalRcvBuffSize 1024*64
#define gDefaultLocalClientNums 1024*64

DECLARE_SIMPLE_CLASS(SysTcpSocketObserver) EXTENDS(EPollFileObserverListener){
public:
    _SysTcpSocketObserver(SocketListener,int,EPollFileObserver o);
    int onEvent(int fd,uint32_t events,ByteArray);

private:
    SocketListener mListener;
    EPollFileObserver mObserver;
    int mSock;
};

DECLARE_SIMPLE_CLASS(LocalSocketServer) {
    
public:
    _LocalSocketServer(String domain,SocketListener l,int clients = gDefaultLocalClientNums, int recvsize=gDefaultLocalRcvBuffSize);

    int start();

    int tryStart();

    void release();

    int send(int fd,ByteArray data);

    void setRcvBuffSize(int);

    int getStatus();

    int getSock();

    ~_LocalSocketServer();

private:
    int connect();

    int tryConnect();

    SocketListener mListener;

    EPollFileObserver mEpollFileObserver;

    SysTcpSocketObserver mSysTcpListener;

    struct sockaddr_un serverAddr;

    int sock;

    String mDomain;

    int mConectNum;
};

}
#endif
