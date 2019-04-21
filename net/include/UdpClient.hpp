#ifndef __UDP_CLIENT_HPP__
#define __UDP_CLIENT_HPP__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <memory.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "SocketPacket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(UdpClient) {
public:
    _UdpClient(String ip,int port,SocketListener listener);

    int send(SocketPacket p);

    int send(String);

    void start();

private:

    bool init();

    void addfd(int epollfd, int fd, bool enable_et);

    int sock;

    int epfd;

    struct sockaddr_in serverAddr;

    SocketListener listener;
};

}
#endif
