#ifndef __ASYNC_TCP_CLIENT_HPP__
#define __ASYNC_TCP_CLIENT_HPP__

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

enum TcpClientStatus {
    ClientWorking = 1,
    ClientWaitingThreadExit,
    ClientThreadExited,
};

DECLARE_SIMPLE_CLASS(TcpClientThread) EXTENDS(Thread){
public:
    _TcpClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status,int timeout,int buffersize);

    void run();

private:
    int mSock;

    int mEpfd;

    SocketListener mListener;

    Pipe mPipe;

    AtomicInteger mStatus;

    int mTimeOut;

    int mBufferSize;
    
};

DECLARE_SIMPLE_CLASS(AsyncTcpClient) {
public:
    _AsyncTcpClient(String ip,int port,int recv_time,SocketListener listener,int buffer_size=64*1024);
    
    _AsyncTcpClient(String ip,int port,SocketListener listener,int buffer_size=64*1024);

    _AsyncTcpClient(String ip,int port,int buffer_size=64*1024);

    void start();

    void release();

    void wait();

    int send(ByteArray);

    ~_AsyncTcpClient();

private:

    bool init(String ip,int port,int recv_time,SocketListener l,int buff_size);

    int sock;

    int epfd;

    struct sockaddr_in serverAddr;

    SocketListener listener;

    TcpClientThread mTcpClientThread;

    Pipe mPipe;

    AtomicInteger mStatus;

    int mRecvtimeout;

    int mBuffSize;

};

}
#endif
