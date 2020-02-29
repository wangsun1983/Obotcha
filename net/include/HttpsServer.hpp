#ifndef __HTTP_SSL_SERVER_HPP__
#define __HTTP_SSL_SERVER_HPP__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <stddef.h>

extern "C" {
#include "openssl/ssl.h"
#include "openssl/err.h"
}


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "AtomicInteger.hpp"
#include "Thread.hpp"
#include "SocketListener.hpp"
#include "TcpServer.hpp"

namespace obotcha {

enum HttpsServerStatus {
    HttpsServerNotStart = 1,
    HttpsServerWorking,
    HttpsServerWaitingThreadExit,
    HttpsServerThreadExited,
};  

DECLARE_SIMPLE_CLASS(HttpsThread) IMPLEMENTS(Thread) {
public:
    _HttpsThread(String ip,int port,SocketListener l,String certificate,String key);

    void run();

private:
    SSL * initSSL();

    int mSocket;
    int mEpollfd;
    Pipe mPipe;
    SocketListener mListener;
    Mutex mClientMutex;
    int mBuffSize;
    String mIp;
    int mPort; 
    struct sockaddr_in mSockAddr;

    int mRcvBuffSize;
    int mClientNums;

    String mCertificate;

    String mKey;

    HashMap<int,SSL *>mClients;

}; 

DECLARE_SIMPLE_CLASS(HttpsServer) {

public:
    _HttpsServer(int port,SocketListener l,String certificate,String key);

    _HttpsServer(String ip,int port,SocketListener l,String certificate,String key);

    _HttpsServer(String ip,int port,int rcvBuffsize,int connectionsNum,SocketListener l,String certificate,String key);

    void setRcvBuffSize(int);

    int getRcvBuffSize();

    int start();

    void release();
   
    int removeClientFd(int fd);

    int addClientFd(int fd);

    int getStatus();

    ~_HttpsServer();

private:
    
    SocketListener mListener;

    HttpsThread mHttpThread;

};

}
#endif
