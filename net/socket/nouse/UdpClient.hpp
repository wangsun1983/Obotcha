#ifndef __OBOTCHA_UDP_CLIENT_HPP__
#define __OBOTCHA_UDP_CLIENT_HPP__

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


DECLARE_SIMPLE_CLASS(UdpClient) IMPLEMENTS(EPollFileObserverListener) {
public:

    _UdpClient(int port,SocketListener l);

    _UdpClient(String ip,int port,SocketListener l);

    void start();

    void release();

    int send(ByteArray);

    ~_UdpClient();

private:

    int onEvent(int fd,uint32_t events,ByteArray);

    int sock;

    int epfd;

    struct sockaddr_in serverAddr;

    SocketListener listener;

    EPollFileObserver mObserver;

};

}
#endif
