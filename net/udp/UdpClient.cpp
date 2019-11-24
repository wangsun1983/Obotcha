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

#include "UdpClient.hpp"
#include "NetUtils.hpp"

#define EPOLL_SIZE 128

#define BUF_SIZE 1024*64

namespace obotcha {

_UdpClientThread::_UdpClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status) {
    mSock = sock;
    mEpfd = epfd;
    mListener = l;
    mPipe = pi;
    mStatus = status;
}

void _UdpClientThread::run() {
    
    struct epoll_event events[EPOLL_SIZE];
    byte recv_buf[BUF_SIZE];
    struct sockaddr_in src;
    socklen_t len = 0;

    memset(&src,0,sizeof(struct sockaddr_in));
    memset(recv_buf,0,BUF_SIZE);
    memset(events,0,sizeof(struct epoll_event)*EPOLL_SIZE);

    while(1) {
        if(mStatus->get() == UdpClientWaitingThreadExit) {
            mStatus->set(UdpClientThreadExited);
            return;
        }
        printf("client udp accept sockfd trace1 !!!! \n");
        int epoll_events_count = epoll_wait(mEpfd, events, EPOLL_SIZE, -1);
        printf("client udp accept sockfd trace2,epoll_events_count is %d !!!! \n",epoll_events_count);
        

        for(int i = 0; i < epoll_events_count ; ++i) {

            int sockfd = events[i].data.fd;
            int event = events[i].events;
            //printf("udp accept sockfd trace3,sockfd is %d,events is %d !!!! \n",sockfd,events);

            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                printf("client wangsl,mPipe event is %x \n",event);
                if(mStatus->get() == UdpClientWaitingThreadExit) {
                    mStatus->set(UdpClientThreadExited);
                    printf("client wangsl,mPipe exit \n");
                    return;
                }
                
                continue;
            }

            
            if(events[i].data.fd == mSock) {
                //int ret = recv(mSock, recv_buf, BUF_SIZE, 0);
                int ret = recvfrom(mSock, recv_buf, BUF_SIZE, 0, (struct sockaddr*)&src, &len);
                //if(ret > 0) {
                //    cout << "Server closed connection: " << mSock << endl;
                //    st(NetUtils)::delEpollFd(mEpfd,sockfd);
                //    mListener->onDisconnect(sockfd);
                //    close(sockfd);
                //    mStatus->set(UdpClientThreadExited);
                //    return;
                //} else {
                    //onAcceptUdp(int fd,String ip,int port,ByteArray pack) {};
                printf("client receive from result is %d \n",ret);

                if(ret > 0) {
                    printf("client accept recv_buf is %s \n",recv_buf);
                    ByteArray pack = createByteArray(recv_buf,ret);
                    mListener->onAccept(mSock,
                                        createString(inet_ntoa(src.sin_addr)), 
                                        ntohs(src.sin_port), 
                                        pack);
                }                        
                //}
            }
        }
    }
}

_UdpClient::_UdpClient(int port,SocketListener l):_UdpClient{nullptr,port,l} {

}

_UdpClient::_UdpClient(String ip,int port,SocketListener l) {

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if(ip != nullptr) {
        serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    } else {
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    //std::cout << "Connect Server: " << ip->toChars() << " : " << port << endl;
    epfd = -1;

    listener = l;

    mPipe = createPipe();

    mPipe->init();

    mStatus = createAtomicInteger(UdpClientWorking);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
}

bool _UdpClient::init() {
    printf("UdpClient init start \n");
    //sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        return false;
    }
    printf("UdpClient init trace1 \n");
    //if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    //    return false;
    //}
 
    epfd = epoll_create(EPOLL_SIZE);
    printf("UdpClient init trace2 \n");
    if(epfd < 0) {
        return false;
    }
 
    //addfd(epfd, sock, true);
    st(NetUtils)::addEpollFd(epfd, sock, true);
    st(NetUtils)::addEpollFd(epfd, mPipe->getReadPipe(), true);
    printf("UdpClient init end \n");
    return true;
}

int _UdpClient::send(ByteArray data) {
    //return st(NetUtils)::sendUdpPacket(sock,data);
    return st(NetUtils)::sendUdpPacket(sock,&serverAddr,data);
}

_UdpClient::~_UdpClient() {
    release();
}

void _UdpClient::start() {
    
    init();
    mUdpClientThread = createUdpClientThread(sock,epfd,listener,mPipe,mStatus);
    mUdpClientThread->start();
}

void _UdpClient::release() {

    if(mStatus->get() == UdpClientWaitingThreadExit || mStatus->get() == UdpClientThreadExited) {
        return;
    }
    
    printf("_UdpClient sock is %d \n",sock);
    if(sock != -1) {
        close(sock);
        sock = -1;
    }
    
    if(mUdpClientThread != nullptr) {
        if(mStatus->get() != UdpClientThreadExited) {
            mStatus->set(UdpClientWaitingThreadExit);
        }

        mPipe->writeTo(createByteArray(1));

        while(mStatus->get() != UdpClientThreadExited) {
            //TODO
        }
    }

    if(epfd != -1) {
        close(epfd);
    }
    
}

}