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
#include "Thread.hpp"
#include "EPollFileObserver.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(LocalSocketServer) EXTENDS(EPollFileObserverListener) {
    
public:
    static const int DefaultLocalRcvBuffSize;
    static const int DefaultLocalClientNums;

    _LocalSocketServer(String domain,SocketListener l,int clients = DefaultLocalClientNums, int recvsize=DefaultLocalRcvBuffSize);

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

    int onEvent(int fd,uint32_t events,ByteArray);

    SocketListener mListener;

    EPollFileObserver mEpollFileObserver;

    struct sockaddr_un serverAddr;

    int sock;

    String mDomain;

    int mConectNum;
};

}
#endif
