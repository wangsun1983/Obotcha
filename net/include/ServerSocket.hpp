#ifndef __SERVER_SOCKET_HPP__
#define __SERVER_SOCKET_HPP__

#include <netinet/in.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketPacket.hpp"
#include "SocketListener.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ServerSocket) {
public:
    _ServerSocket(int port,SocketListener l);

    _ServerSocket(String ip,int port,SocketListener l);

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
