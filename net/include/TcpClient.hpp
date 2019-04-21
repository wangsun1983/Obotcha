#ifndef __TCP_CLIENT_HPP__
#define __TCP_CLIENT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
namespace obotcha {

DECLARE_SIMPLE_CLASS(TcpClient) {
public:
    _TcpClient(String ip,int port,SocketListener listener);

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
