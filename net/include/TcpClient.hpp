#ifndef __OBOTCHA_TCP_CLIENT_HPP__
#define __OBOTCHA_TCP_CLIENT_HPP__

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
#include "EPollFileObserver.hpp"

namespace obotcha {

class _TcpClient;

DECLARE_SIMPLE_CLASS(LocalTcpClientListener) IMPLEMENTS(EPollFileObserverListener) {
public:
    _LocalTcpClientListener(SocketListener l,sp<_TcpClient> client);

    int onEvent(int fd,uint32_t events,ByteArray);

private:
    SocketListener mListener;
    sp<_TcpClient> mClient;
};

DECLARE_SIMPLE_CLASS(TcpClient) {
public:
    _TcpClient(int port,int recv_time,SocketListener l = nullptr,int buff_size = 1024);

    _TcpClient(String ip,int port,int recv_time,SocketListener l = nullptr,int buff_size = 1024);

    int doConnect();

    int doSend(ByteArray);

    ByteArray doReceive();

    int getBuffSize();

    void release();

    int getSock();

    ~_TcpClient();

private:
    int mReceiveTimeout;

    EPollFileObserver mEpollObserver;

    LocalTcpClientListener mLocalTcpListener;
    
    int mSock;

    struct sockaddr_in serverAddr;

    int mBufferSize;

    byte *mBuff;

    Mutex mConnectMutex;

    SocketListener mListener;
};

}
#endif
