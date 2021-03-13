#ifndef __OBOTCHA_LOCAL_SOCKET_CLIENT_HPP__
#define __OBOTCHA_LOCAL_SOCKET_CLIENT_HPP__

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


DECLARE_SIMPLE_CLASS(LocalSocketClient) EXTENDS(EPollFileObserverListener) {
public:
    _LocalSocketClient(String domain,int recv_time,int buff_size = 1024,SocketListener l = nullptr);
    
    int doConnect();

    int doSend(ByteArray);

    ByteArray doRead();

    ByteArray doReceive();

    int getBuffSize();

    void release();

    int getSock();

    ~_LocalSocketClient();

private:
    int onEvent(int fd,uint32_t events,ByteArray);

    int mReceiveTimeout;
    
    int mSock;

    struct sockaddr_un serverAddr;

    int mBufferSize;

    EPollFileObserver mObserver;

    SocketListener mSocketListener;

    Mutex mConnectMutex;

    String mDomain;
};

}
#endif
