#ifndef __TCP_SERVER_HPP__
#define __TCP_SERVER_HPP__

#include <netinet/in.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketPacket.hpp"
#include "SocketListener.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(TcpServer) {
public:
    _TcpServer(int port,SocketListener l);

    _TcpServer(String ip,int port,SocketListener l);

    bool start();

    void close();

private:
    bool connect();

    void addfd(int epollfd, int fd, bool enable_et);

    SocketListener mListener;

    struct sockaddr_in serverAddr;

    int sock;

    int epfd;
};

}
#endif
