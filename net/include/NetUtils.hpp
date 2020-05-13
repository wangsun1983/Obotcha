#ifndef __OBOTCHA_NETUTILS_HPP__
#define __OBOTCHA_NETUTILS_HPP__

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
#include "ArrayList.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(NetUtils) {

public:
    static int addEpollFd(int epollfd, int fd, bool enable_et);
    static int delEpollFd(int epollfd, int fd);

    static int sendTcpPacket(int fd,ByteArray packet);

    static int sendUdpPacket(String ip,int port,ByteArray packet);
    static int sendUdpPacket(int udpsocket,String ip,int port,ByteArray packet);

    static int sendUdpPacket(struct sockaddr_in *serverAddr,ByteArray packet);
    static int sendUdpPacket(int udpsocket,struct sockaddr_in *serverAddr,ByteArray packet);
};

}
#endif
