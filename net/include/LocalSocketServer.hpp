#ifndef __LOCAL_SOCKET_SERVER_HPP__
#define __LOCAL_SOCKET_SERVER_HPP__

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

#define gDefaultLocalRcvBuffSize 1024*64
#define gDefaultLocalClientNums 1024*64

enum LocalSocketServerStatus {
    LocalServerNotStart = 1,
    LocalServerWorking ,
    LocalServerWaitingThreadExit,
    LocalServerThreadExited,
};

DECLARE_SIMPLE_CLASS(LocalSocketServerThread) EXTENDS(Thread){

public:
    _LocalSocketServerThread(int sock,
                    int epfd,
                    AtomicInteger status,
                    Pipe pi,
                    SocketListener listener,
                    ArrayList<Integer> clients,
                    Mutex mutex,
                    String domain,
                    int buffsize);
    void run();

    void setRcvBuffSize(int);

private:
    int mSocket;
    int mEpollfd;
    AtomicInteger mStatus;
    Pipe mPipe;
    SocketListener mListener;
    ArrayList<Integer> mClients;
    Mutex mClientMutex;
    String mDomain;

    int mBuffSize;

    void addClientFd(int fd);

    void removeClientFd(int fd);
};


DECLARE_SIMPLE_CLASS(LocalSocketServer) {
    
public:
    _LocalSocketServer(String domain,SocketListener l,int clients = gDefaultLocalClientNums, int recvsize=gDefaultLocalRcvBuffSize);

    int start();

    void release();

    int send(int fd,ByteArray data);

    void setRcvBuffSize(int);

    int getStatus();

    ~_LocalSocketServer();

private:
    int connect();

    SocketListener mListener;

    struct sockaddr_un serverAddr;

    int sock;

    int epfd;

    int mClientsNum;

    Pipe mPipe;

    AtomicInteger mStatus;

    LocalSocketServerThread mServerThread;

    Mutex mClientsMutex;

    ArrayList<Integer> mClients;

    String mDomain;
};

}
#endif
