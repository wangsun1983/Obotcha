#ifndef __LOCAL_SOCKET_SERVER_HPP__
#define __LOCAL_SOCKET_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "LocalSocketServer.hpp"
#include "SocketListener.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(LocalSocketServer) {

public:
    _LocalSocketServer(String domain,SocketListener l);

    bool start();

    void close();

private:
    bool connect();

    void addfd(int epollfd, int fd, bool enable_et);

    SocketListener mListener;

    struct sockaddr_un serverAddr;

    int sock;

    int epfd;

    String mDomain;

};

}
#endif
