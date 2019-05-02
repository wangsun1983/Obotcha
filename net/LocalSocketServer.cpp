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


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "LocalSocketServer.hpp"
#include "SocketListener.hpp"


#define EPOLL_SIZE 5000

#define BUFF_SIZE 1024*64

namespace obotcha {

_LocalSocketServer::_LocalSocketServer(String domain,SocketListener l) {
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars());   

    sock = 0;
    epfd = 0;

    mListener = l;

    mDomain = domain;
}

bool _LocalSocketServer::connect() {
    printf("LocalSocketServer connect start \n");
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    if(sock < 0) {
        return false;
    }
    printf("LocalSocketServer connect trace1 \n");

    unlink(mDomain->toChars());

    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);   

    printf("LocalSocketServer connect trace2,len is %d \n",len);

    if( bind(sock, (struct sockaddr *)&serverAddr, len) < 0) {
        printf("bind server faild , error = %s \n", strerror(errno));
        return false;
    }

    printf("LocalSocketServer connect trace3 \n");

    int ret = listen(sock, 5);

    if(ret < 0) {
        return false;
    }
    printf("LocalSocketServer connect trace4 \n");

    epfd = epoll_create(EPOLL_SIZE);
    if(epfd < 0) {
        return false;
    }
    printf("LocalSocketServer connect trace5 \n");
    //add epoll
    addfd(epfd,sock,true);
    printf("LocalSocketServer connect trace6 \n");
    return true;
}

void _LocalSocketServer::addfd(int epollfd, int fd, bool enable_et) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
}

bool _LocalSocketServer::start() {
    // epoll 事件队列
    static struct epoll_event events[EPOLL_SIZE];
    printf("LocalSocketServer start trace1 \n");
    if(!connect()) {
        return false;
    }
    printf("LocalSocketServer start trace2 \n");

    while(1) {

        int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        printf("LocalSocketServer start trace3 \n");
        if(epoll_events_count < 0) {
            //TODO
            break;
        }

        printf("LocalSocketServer start trace4 \n");
 
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

    return false;
}

void _LocalSocketServer::close() {
    //TODO
}

}
