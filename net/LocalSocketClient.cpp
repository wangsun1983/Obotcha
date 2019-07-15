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

#include "LocalSocketClient.hpp"
#include "NetUtils.hpp"

#define EPOLL_SIZE 128

#define BUF_SIZE 1024*64

namespace obotcha {

_LocalSocketClientThread::_LocalSocketClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status) {
    mSock = sock;
    mEpfd = epfd;
    mListener = l;
    mPipe = pi;
    mStatus = status;
}

void _LocalSocketClientThread::run() {
    
    struct epoll_event events[EPOLL_SIZE];
    char recv_buf[BUF_SIZE];

    while(1) {
        if(mStatus->get() == LocalSocketClientWaitingThreadExit) {
            mStatus->set(LocalSocketClientThreadExited);
            return;
        }

        int epoll_events_count = epoll_wait(mEpfd, events, EPOLL_SIZE, -1);

        for(int i = 0; i < epoll_events_count ; ++i) {

            int sockfd = events[i].data.fd;
            int event = events[i].events;

            if(((event&EPOLLIN) != 0) 
            && ((event &EPOLLRDHUP) != 0)) {
                printf("hangup sockfd!!!! \n");
                if(sockfd == mSock) {
                    st(NetUtils)::delEpollFd(mEpfd,sockfd);
                    mListener->onDisconnect(sockfd);
                    close(sockfd);
                    mStatus->set(LocalSocketClientThreadExited);
                    return;
                }
            }

            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                printf("wangsl,mPipe event is %x \n",event);
                if(mStatus->get() == LocalSocketClientWaitingThreadExit) {
                    mStatus->set(LocalSocketClientThreadExited);
                    printf("wangsl,mPipe exit \n");
                    return;
                }
                
                continue;
            }

            memset(recv_buf,0,BUF_SIZE);
            if(events[i].data.fd == mSock) {
                int ret = recv(mSock, recv_buf, BUF_SIZE, 0);
                if(ret == 0) {
                    cout << "Server closed connection: " << mSock << endl;
                    st(NetUtils)::delEpollFd(mEpfd,sockfd);
                    mListener->onDisconnect(sockfd);
                    close(sockfd);
                    mStatus->set(LocalSocketClientThreadExited);
                    return;
                } else {
                    ByteArray pack = createByteArray(recv_buf,ret);
                    mListener->onAccept(mSock,nullptr,-1,pack);
                }
            }
        }
    }
}

_LocalSocketClient::_LocalSocketClient(String domain,SocketListener l) {

    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars()); 

    epfd = 0;
    sock = 0;

    listener = l;

    mPipe = createPipe();
    mPipe->init();

    mStatus = createAtomicInteger(LocalSocketClientWorking);
    epfd = epoll_create(EPOLL_SIZE);
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
}

bool _LocalSocketClient::init() {
    printf("TcpClient init start \n");
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);  
    printf("LocalSocketClient init trace3 \n");
    if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("connect error :%s \n",strerror(errno));
        return false;
    }
    printf("LocalSocketClient init trace4 \n");

    st(NetUtils)::addEpollFd(epfd, sock,true);
    return true;
}

int _LocalSocketClient::send(ByteArray data) {
    return st(NetUtils)::sendTcpPacket(sock,data);
}

void _LocalSocketClient::start() {
    
    init();
    mLocalSocketClientThread = createLocalSocketClientThread(sock,epfd,listener,mPipe,mStatus);
    mLocalSocketClientThread->start();
}

void _LocalSocketClient::release() {
    close(sock);
    sock = 0;

    if(mStatus->get() != LocalSocketClientThreadExited) {
        mStatus->set(LocalSocketClientWaitingThreadExit);
    }

    mPipe->writeTo(createByteArray(1));

    while(mStatus->get() != LocalSocketClientThreadExited) {

    }

    close(epfd);
}

}