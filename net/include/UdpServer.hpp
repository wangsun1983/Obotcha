#ifndef __OBOTCHA_UDP_SERVER_HPP__
#define __OBOTCHA_UDP_SERVER_HPP__

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

enum UdpServerStatus {
    UdpServerIdle = 1,
    UdpServerWorking,
    UdpServerWaitingThreadExit,
    UdpServerThreadExited,
};

DECLARE_SIMPLE_CLASS(UdpServerThread) EXTENDS(Thread){

public:
    _UdpServerThread(int sock,
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

DECLARE_SIMPLE_CLASS(UdpServer) {
    
public:
    _UdpServer(int port,SocketListener l);

    _UdpServer(String ip,int port,SocketListener l);

    int start();

    void release();

    //int send(String ip,int port,ByteArray data);

    ~_UdpServer();

private:
    int connect();

    SocketListener mListener;

    struct sockaddr_in serverAddr;

    int sock;

    int epfd;

    Pipe mPipe;

    AtomicInteger mStatus;

    UdpServerThread mServerThread;

    Mutex mClientsMutex;

    ArrayList<Integer> mClients;
};

}
#endif
