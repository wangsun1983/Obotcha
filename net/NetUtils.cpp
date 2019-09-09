#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <stddef.h>
#include <errno.h>


#include "NetUtils.hpp"

namespace obotcha {

int _NetUtils::addEpollFd(int epollfd, int fd, bool enable_et) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLRDHUP |EPOLLHUP;
    if( enable_et )
        ev.events |= EPOLLET;
    int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0) {
        return ret;
    }
    
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
}

int _NetUtils::delEpollFd(int epollfd, int fd) {
    return epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}

int _NetUtils::sendTcpPacket(int fd,ByteArray packet) {
    return write(fd,packet->toValue(),packet->size());
}

int _NetUtils::sendUdpPacket(int udpsocket,String ip,int port,ByteArray packet) {
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip->toChars());
    int server_len = sizeof(struct sockaddr_in);     
    int result = sendto(udpsocket, packet->toValue(),  packet->size(), 0, (struct sockaddr *)&server, server_len);
    //printf("send udp1 result is %d error is %s \n",result,strerror(errno));
    return result;
}

int _NetUtils::sendUdpPacket(int udpsocket,struct sockaddr_in *serverAddr,ByteArray packet) {
    int server_len = sizeof(struct sockaddr_in);
    printf("send udp2 packet,packet is %s \n",packet->toValue());
    int result = sendto(udpsocket, packet->toValue(),  packet->size(), 0, (struct sockaddr *)serverAddr, server_len);
    printf("send udp2 result is %d error is %s \n",result,strerror(errno));
    return result;
}



}
