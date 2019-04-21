#ifndef __UDP_SERVER_HPP__
#define __UDP_SERVER_HPP__

#include <netinet/in.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketPacket.hpp"
#include "SocketListener.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(UdpServer) {
public:
    _UdpServer(int port,SocketListener l);

    _UdpServer(String ip,int port,SocketListener l);

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
