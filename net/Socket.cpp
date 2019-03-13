#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <memory.h>

#include "Socket.hpp"

#define EPOLL_SIZE 5000

#define BUF_SIZE 1024*64

_Socket::_Socket(String ip,int port,SocketListener l) {

    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    std::cout << "Connect Server: " << ip->toChars() << " : " << port << endl;
    epfd = 0;
    sock = 0;

    listener = l;
}

bool _Socket::init() {
   
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        return false;
    }
 
    if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        return false;
    }
 
    epfd = epoll_create(EPOLL_SIZE);
    
    if(epfd < 0) {
        return false;
    }
 
    addfd(epfd, sock, true);
}

void _Socket::addfd(int epollfd, int fd, bool enable_et) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
}

void _Socket::start() {
    
    init();

    static struct epoll_event events[2];
    char recv_buf[BUF_SIZE];

    while(1) {
        int epoll_events_count = epoll_wait( epfd, events, 2, -1 );

        for(int i = 0; i < epoll_events_count ; ++i) {
            memset(recv_buf,0,BUF_SIZE);
            if(events[i].data.fd == sock) {

                int ret = recv(sock, recv_buf, BUF_SIZE, 0);
                if(ret == 0) {
                    cout << "Server closed connection: " << sock << endl;
                    //close(sock);
                    //isClientwork = 0;
                    listener->onDisconnect(sock);
                } else {
                    SocketPacket pack = createSocketPacket(recv_buf,ret);
                    listener->onAccept(sock,pack);
                }
            }
        }
    }
}