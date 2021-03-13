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
#include "Thread.hpp"
#include "EPollFileObserver.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(UdpServer) IMPLEMENTS(EPollFileObserverListener) {
    
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

    int onEvent(int fd,uint32_t events,ByteArray);

    EPollFileObserver mEpollObserver;

    Mutex mClientsMutex;

    ArrayList<Integer> mClients;
};

}
#endif
