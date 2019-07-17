#ifndef __TCP_CLIENT_HPP__
#define __TCP_CLIENT_HPP__

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
    _TcpClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status,int timeout);

    void run();

private:
    int mSock;

    int mEpfd;

    SocketListener mListener;

    Pipe mPipe;

    AtomicInteger mStatus;

    int mTimeOut;
    
};

DECLARE_SIMPLE_CLASS(TcpClient) {
public:
    _TcpClient(String ip,int port,int recv_time,SocketListener listener);
    
    _TcpClient(String ip,int port,SocketListener listener);

    void start();

    void release();

    void wait();

    int send(ByteArray);

    ~_TcpClient();

private:

    bool init(String ip,int port,int recv_time,SocketListener l);

    int sock;

    int epfd;

    struct sockaddr_in serverAddr;

    SocketListener listener;

    TcpClientThread mTcpClientThread;

    Pipe mPipe;

    AtomicInteger mStatus;

    int mRecvtimeout;

};

}
#endif
