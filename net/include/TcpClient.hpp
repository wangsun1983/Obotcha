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

DECLARE_SIMPLE_CLASS(TcpClient) EXTENDS(EPollFileObserverListener){
public:
    _TcpClient(int port,SocketListener l = nullptr,int buff_size = 1024);

    _TcpClient(String ip,int port,SocketListener l = nullptr,int buff_size = 1024);
    
    void setSendTimeout(long);
    long getSendTimeout();

    void setRcvTimeout(long);
    long getRcvTimeout();

    int doConnect();

    int doSend(ByteArray);

    ByteArray doReceive();

    int getBuffSize();

    void release();

    int getSock();

    ~_TcpClient();

private:
    int onEvent(int fd,uint32_t events,ByteArray);

    int mReceiveTimeout;

    EPollFileObserver mEpollObserver;
    
    int mSock;

    struct sockaddr_in serverAddr;

    int mBufferSize;

    SocketListener mListener;

    String mServerIp;

    int mServerPort;

    long mSendTimeout;

    long mRcvTimeout;
};

}
#endif
