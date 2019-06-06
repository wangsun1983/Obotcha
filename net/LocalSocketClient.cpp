#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <fstream>
#include <sys/socket.h>  
#include <sys/un.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stddef.h>
#include <sys/ioctl.h>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "LocalSocketClient.hpp"

namespace obotcha {

#define EPOLL_SIZE 5000

#define BUF_SIZE 1024*64


_LocalSocketClient::_LocalSocketClient(String domain,SocketListener l) {

    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars());  

    epfd = 0;
    sock = 0;

    listener = l;

    mDomain = domain;
}

bool _LocalSocketClient::init() {
    printf("LocalSocketClient init trace1 \n");
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock < 0) {
        return false;
    }
    printf("LocalSocketClient init trace2 \n");
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);  
    printf("LocalSocketClient init trace3 \n");
    if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("connect error :%s \n",strerror(errno));
        return false;
    }
    printf("LocalSocketClient init trace4 \n");
    epfd = epoll_create(EPOLL_SIZE);
    
    if(epfd < 0) {
        return false;
    }
    printf("LocalSocketClient init trace5 \n");
    addfd(epfd, sock, true);
    return false;
}

void _LocalSocketClient::addfd(int epollfd, int fd, bool enable_et) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
}

void _LocalSocketClient::start() {
    printf("LocalSocketClient start trace1 \n");
    init();
    if(1) {
        return;
    }
    printf("LocalSocketClient start trace2 \n");
    static struct epoll_event events[2];
    char recv_buf[BUF_SIZE];
    printf("LocalSocketClient start trace3 \n");
    while(1) {
        int epoll_events_count = epoll_wait( epfd, events, 2, -1 );
        printf("LocalSocketClient start trace4 \n");
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

void _LocalSocketClient::send(ByteArray arr) {
    write(sock, arr->toValue(), arr->size());
}

}

