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

enum LocalSocketClientStatus {
    LocalSocketClientWorking = 1,
    LocalSocketClientWaitingThreadExit,
    LocalSocketClientThreadExited,
};

DECLARE_SIMPLE_CLASS(LocalSocketClientThread) EXTENDS(Thread){
public:
    _LocalSocketClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status);

    void run();

private:
    int mSock;

    int mEpfd;

    SocketListener mListener;

    Pipe mPipe;

    AtomicInteger mStatus;
    
};

DECLARE_SIMPLE_CLASS(LocalSocketClient) {
public:
    _LocalSocketClient(String domain,SocketListener listener);

    void start();

    void release();

    int send(ByteArray);

private:

    bool init();

    int sock;

    int epfd;

    struct sockaddr_un serverAddr;

    SocketListener listener;

    LocalSocketClientThread mLocalSocketClientThread;

    Pipe mPipe;

    AtomicInteger mStatus;

};

}
#endif
