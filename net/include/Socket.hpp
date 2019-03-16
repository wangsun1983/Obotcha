#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
namespace obotcha {

DECLARE_SIMPLE_CLASS(Socket) {
public:
    _Socket(String ip,int port,SocketListener listener);

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
