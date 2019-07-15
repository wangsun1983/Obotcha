#ifndef __TCP_SERVER_HPP__
#define __TCP_SERVER_HPP__

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

namespace obotcha {

enum TcpServerFailReason {
    TcpServerBindFailed = 200,
    TcpServerListenFailed,
    TcpServerCreateEpollFailed,
    TcpServerEpollWaitFailed,
    TcpServerEpollForceExit,
};

enum TcpServerStatus {
    ServerWorking = 1,
    ServerWaitingThreadExit,
    ServerThreadExited,
};

DECLARE_SIMPLE_CLASS(TcpServerThread) EXTENDS(Thread){

public:
    _TcpServerThread(int sock,
                    int epfd,
                    AtomicInteger status,
                    Pipe pi,
                    SocketListener listener,
                    ArrayList<Integer> clients,
                    Mutex mutex);
    void run();

private:
    int mSocket;
    int mEpollfd;
    AtomicInteger mStatus;
    Pipe mPipe;
    SocketListener mListener;
    ArrayList<Integer> mClients;
    Mutex mClientMutex;

    void addClientFd(int fd);

    void removeClientFd(int fd);
};

DECLARE_SIMPLE_CLASS(TcpServer) {
    
public:
    _TcpServer(int port,SocketListener l);

    _TcpServer(String ip,int port,SocketListener l);

    int start();

    void release();

    int send(int fd,ByteArray data);

    ~_TcpServer();

private:
    int connect();

    SocketListener mListener;

    struct sockaddr_in serverAddr;

    int sock;

    int epfd;

    Pipe mPipe;

    AtomicInteger mStatus;

    TcpServerThread mServerThread;

    Mutex mClientsMutex;

    ArrayList<Integer> mClients;
};

}
#endif
