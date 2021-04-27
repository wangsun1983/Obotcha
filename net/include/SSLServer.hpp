#ifndef __OBOTCHA_SSL_SERVER_HPP__
#define __OBOTCHA_SSL_SERVER_HPP__

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
#include "Thread.hpp"
#include "SocketListener.hpp"
#include "SSLInfo.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SSLThread) IMPLEMENTS(Thread) {
public:
    _SSLThread(String ip,int port,SocketListener l,String certificate,String key);

    void run();

private:
    int mSocket;
    int mEpollfd;
    Pipe mPipe;
    SocketListener mListener;
    Mutex mClientMutex;
    String mIp;
    int mPort; 
    struct sockaddr_in mSockAddr;

    String mCertificate;
    String mKey;

    int mRcvBuffSize;
    int mClientNums;

    int addEpollFd(int epollfd, int fd, bool enable_et);
    
    int delEpollFd(int epollfd, int fd);

    Mutex mMutex;
    HashMap<int,Socket> mSocks;

}; 

DECLARE_SIMPLE_CLASS(SSLServer) {

public:
    _SSLServer(int port,SocketListener l,String certificate,String key);

    _SSLServer(String ip,int port,SocketListener l,String certificate,String key);

    _SSLServer(String ip,int port,int rcvBuffsize,int connectionsNum,SocketListener l,String certificate,String key);

    void setRcvBuffSize(int);

    int getRcvBuffSize();

    void start();

    void close();
   
    int removeClientFd(int fd);

    int addClientFd(int fd);

    int getStatus();

    ~_SSLServer();

    

private:
    
    SocketListener mListener;

    SSLThread mSSLThread;

};

}
#endif
