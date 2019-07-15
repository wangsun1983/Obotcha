#ifndef __UDP_CLIENT_HPP__
#define __UDP_CLIENT_HPP__

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

enum UdpClientStatus {
    UdpClientWorking = 1,
    UdpClientWaitingThreadExit,
    UdpClientThreadExited,
};

DECLARE_SIMPLE_CLASS(UdpClientThread) EXTENDS(Thread){
public:
    _UdpClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status);

    void run();

private:
    int mSock;

    int mEpfd;

    SocketListener mListener;

    Pipe mPipe;

    AtomicInteger mStatus;
    
};

DECLARE_SIMPLE_CLASS(UdpClient) {
public:
    _UdpClient(String ip,int port,SocketListener l);

    void start();

    void release();

    int send(ByteArray);

private:

    bool init();

    int sock;

    int epfd;

    struct sockaddr_in serverAddr;

    SocketListener listener;

    UdpClientThread mUdpClientThread;

    Pipe mPipe;

    AtomicInteger mStatus;

};

}
#endif
