#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <memory.h>

#include "UdpServer.hpp"

//https://blog.csdn.net/lewis1993_cpapa/article/details/80589717
#define EPOLL_SIZE 5000

#define BUFF_SIZE 1024*64

namespace obotcha {

_UdpServer::_UdpServer(int port,SocketListener l) {
    //TODO
}

_UdpServer::_UdpServer(String ip,int port,SocketListener l) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());

    sock = 0;
    epfd = 0;

    mListener = l;
}

bool _UdpServer::connect() {
    //int opt = 1;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    //setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    int opt = SO_REUSEADDR;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    //if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
    //    printf("fnctl failed \n");
    //    return false;
    //}
    epfd = epoll_create(EPOLL_SIZE);
    if(epfd < 0) {
        printf("UdpServer create epool fail \n");
        return false;
    }

    //add epoll
    addfd(epfd,sock,true);

    if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("bind server faild , error = %s \n", strerror(errno));
        return false;
    }

    //int ret = listen(sock, 5);
    //if(ret < 0) {
    //    printf("UdpServer bind fail \n");
    //    return false;
    //}


    
    return true;
}

void _UdpServer::addfd(int epollfd, int fd, bool enable_et) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
}

bool _UdpServer::start() {
    // epoll 事件队列
    static struct epoll_event events[EPOLL_SIZE];
    printf("udpserver trace1 \n");
    if(!connect()) {
        return false;
    }
    printf("udpserver trace2 \n");
    while(1) {
        printf("udpserver trace3 \n");
        int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        printf("udpserver trace3_1 \n");
        if(epoll_events_count < 0) {
            //TODO
            break;
        }
 
        std::cout << "epoll_events_count =\n" << epoll_events_count << endl;
 
        for(int i = 0; i < epoll_events_count; ++i) {
            int sockfd = events[i].data.fd;
            
            if(sockfd == sock) {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                int clientfd = accept( sock, ( struct sockaddr* )&client_address, &client_addrLength );
 
                std::cout << "client connection from: "
                     << inet_ntoa(client_address.sin_addr) << ":"
                     << ntohs(client_address.sin_port) << ", clientfd = "
                     << clientfd << endl;
 
                addfd(epfd, clientfd, true);

                mListener->onConnect(clientfd);
            }
            else {
                char recv_buf[BUFF_SIZE];
                int len = recv(sockfd, recv_buf, BUFF_SIZE, 0);
                SocketPacket pack = createSocketPacket(recv_buf,len);
                if(mListener != nullptr) {
                    mListener->onAccept(sockfd,pack);
                }
            }
        }
    }
}

void _UdpServer::close() {
    //TODO
}

}