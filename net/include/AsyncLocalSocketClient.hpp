#ifndef __OBOTCHA_ASYNC_LOCAL_SOCKET_CLIENT_HPP__
#define __OBOTCHA_ASYNC_LOCAL_SOCKET_CLIENT_HPP__

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
#include "Thread.hpp"
#include "Pipe.hpp"

namespace obotcha {

enum LocalSocketClientStatus {
    LocalSocketClientWorking = 1,
    LocalSocketClientWaitingThreadExit,
    LocalSocketClientThreadExited,
};

DECLARE_SIMPLE_CLASS(AsyncLocalSocketClientThread) EXTENDS(Thread){
public:
    _AsyncLocalSocketClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status,int timeout,int buffersize);

    ~_AsyncLocalSocketClientThread();
    
    void run();

private:
    int mSock;

    int mEpfd;

    SocketListener mListener;

    Pipe mPipe;

    AtomicInteger mStatus;

    int mTimeOut;

    int mBufferSize;

    byte *recvBuff;
    
};

DECLARE_SIMPLE_CLASS(AsyncLocalSocketClient) {
public:
    _AsyncLocalSocketClient(String domain,SocketListener listener,int recvtime = -1,int buffsize = 64*1024);

    void start();

    void release();

    void wait();

    int send(ByteArray);

    ~_AsyncLocalSocketClient();

private:

    bool init();

    int sock;

    int epfd;

    struct sockaddr_un serverAddr;

    SocketListener listener;

    AsyncLocalSocketClientThread mAsyncLocalSocketClientThread;

    Pipe mPipe;

    AtomicInteger mStatus;
    
    int mRecvtimeout;

    int mBuffSize;

};

}
#endif
