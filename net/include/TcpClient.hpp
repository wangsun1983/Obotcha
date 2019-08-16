#ifndef __TCP_CLIENT_HPP__
#define __TCP_CLIENT_HPP__

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

DECLARE_SIMPLE_CLASS(TcpClient) {
public:
    _TcpClient(String ip,int port,int recv_time,int buff_size = 1024*64);
    
    int doConnect();

    int doSend(ByteArray);

    ByteArray doReceive();

    void release();

    ~_TcpClient();

private:
    int mReceiveTimeout;
    
    int mSock;

    struct sockaddr_in serverAddr;

    int mBufferSize;
};

}
#endif
