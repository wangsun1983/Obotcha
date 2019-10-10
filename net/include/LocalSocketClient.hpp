#ifndef __LOCAL_SOCKET_CLIENT_HPP__
#define __LOCAL_SOCKET_CLIENT_HPP__

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

DECLARE_SIMPLE_CLASS(LocalSocketClient) {
public:
    _LocalSocketClient(String domain,int recv_time,int buff_size = 1024);
    
    int doConnect();

    int doSend(ByteArray);

    ByteArray doReceive();

    int getBuffSize();

    void release();

    int getSock();

    ~_LocalSocketClient();

private:
    int mReceiveTimeout;
    
    int mSock;

    struct sockaddr_un serverAddr;

    int mBufferSize;

    char *mBuff;

    Mutex mConnectMutex;

    String mDomain;
};

}
#endif
