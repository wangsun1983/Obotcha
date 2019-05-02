#include "UdpClient.hpp"

#define EPOLL_SIZE 5000

#define BUF_SIZE 1024*64

namespace obotcha {

_UdpClient::_UdpClient(String ip,int port,SocketListener l) {

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    std::cout << "Connect Server: " << ip->toChars() << " : " << port << endl;
    epfd = 0;
    sock = 0;

    listener = l;
}

bool _UdpClient::init() {
    printf("udpclient init 1 \n");
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock < 0) {
        printf("udpclient error 1 \n");
        return false;
    }
    printf("udpclient init 2,sock is %d \n",sock);
    if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("udpclient error 2 \n");
        return false;
    }

/*
    char p[12];
    p[0] = 1;
    p[2] = 2;
    int ret = sendto(sock,p,12,0,(struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
    printf("send value is %d \n",ret);
*/
    printf("udpclient init 3 \n");
    epfd = epoll_create(EPOLL_SIZE);
    
    if(epfd < 0) {
        printf("udpclient error 3 \n");
        return false;
    }

    printf("udpclient init 4 \n");
    addfd(epfd, sock, true);

    return true;
}

void _UdpClient::addfd(int epollfd, int fd, bool enable_et) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if( enable_et )
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
}

int _UdpClient::send(SocketPacket p) {
    char *data = p->data();
    int ret = sendto(sock,data,p->size(),0,(struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
    return ret;
}

int _UdpClient::send(String p) {
    const char *data = p->toChars();
    int ret = sendto(sock,data,p->size(),0,(struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
    return ret;
}

void _UdpClient::start() {
    printf("udpclient start trace1 \n");
    init();
    printf("udpclient start trace2 \n");

    static struct epoll_event events[2];
    char recv_buf[BUF_SIZE];

    while(1) {
        printf("udpclient start trace3\n");
        int epoll_events_count = epoll_wait( epfd, events, 2, -1 );
        printf("udpclient start trace4 \n");

        for(int i = 0; i < epoll_events_count ; ++i) {
            memset(recv_buf,0,BUF_SIZE);
            if(events[i].data.fd == sock) {
                printf("udpclient start 3 \n");
                int ret = recv(sock, recv_buf, BUF_SIZE, 0);
                printf("udpclient start 4 \n");

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

}