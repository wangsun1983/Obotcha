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

class _WebSocketServer;

enum TcpServerStatus {
    ServerNotStart = 1,
    ServerWorking,
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
                    Mutex mutex,
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

    int mBuffSize;

    void addClientFd(int fd);

    void removeClientFd(int fd);
};

DECLARE_SIMPLE_CLASS(TcpServer) {
    
public:
    friend class _WebSocketServer;

    _TcpServer(int port,SocketListener l);

    _TcpServer(String ip,int port,SocketListener l);

    _TcpServer(String ip,int port,int rcvBuffsize,int connectionsNum,SocketListener l);

    void setRcvBuffSize(int);

    int start();

    void release();

    int send(int fd,ByteArray data);

    int removeClientFd(int fd);

    int addClientFd(int fd);

    int getStatus();

    ~_TcpServer();

private:

    int getTcpEpollfd();

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

    int mRcvBuffSize;

    int mConnectionNum;
};

}
#endif
