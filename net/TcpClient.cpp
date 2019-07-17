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

#include "TcpClient.hpp"
#include "NetUtils.hpp"

#define EPOLL_SIZE 128

#define BUF_SIZE 1024*64

namespace obotcha {

_TcpClientThread::_TcpClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status,int timeout) {
    mSock = sock;
    mEpfd = epfd;
    mListener = l;
    mPipe = pi;
    mStatus = status;
    mTimeOut = timeout;
}

void _TcpClientThread::run() {
    
    struct epoll_event events[EPOLL_SIZE];
    char recv_buf[BUF_SIZE];
    printf("epoll run,mTimeOut is %d \n",mTimeOut);
    while(1) {
        if(mStatus->get() == ClientWaitingThreadExit) {
            mStatus->set(ClientThreadExited);
            return;
        }
        printf("epoll trace1 \n");
        int epoll_events_count = epoll_wait(mEpfd, events, EPOLL_SIZE, mTimeOut);
        if(epoll_events_count == 0) {
            printf("epoll_timeout \n");
            return;
        } else if(epoll_events_count < 0) {
            printf("epoll error is %s \n",strerror(errno));
            return;
        }

        printf("epoll trace2 \n");
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
                    mStatus->set(ClientThreadExited);
                    return;
                }
            }

            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                printf("wangsl,mPipe event is %x \n",event);
                if(mStatus->get() == ClientWaitingThreadExit) {
                    mStatus->set(ClientThreadExited);
                    printf("wangsl,mPipe exit \n");
                    return;
                }
                
                continue;
            }

            memset(recv_buf,0,BUF_SIZE);
            if(events[i].data.fd == mSock) {
                printf("epoll trace3 \n");
                int ret = recv(mSock, recv_buf, BUF_SIZE, 0);
                if(ret == 0) {
                    cout << "Server closed connection: " << mSock << endl;
                    st(NetUtils)::delEpollFd(mEpfd,sockfd);
                    mListener->onDisconnect(sockfd);
                    close(sockfd);
                    mStatus->set(ClientThreadExited);
                    return;
                } else {
                    ByteArray pack = createByteArray(recv_buf,ret);
                    mListener->onAccept(mSock,nullptr,-1,pack);
                }
            }
        }
    }
}

_TcpClient::_TcpClient(String ip,int port,int recv_time,SocketListener l) {
    init(ip,port,recv_time,l);
}
    

_TcpClient::_TcpClient(String ip,int port,SocketListener l) {
    init(ip,port,-1,l);
}

bool _TcpClient::init(String ip,int port,int recv_time,SocketListener l) {

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    std::cout << "Connect Server: " << ip->toChars() << " : " << port << endl;
    epfd = 0;
    sock = 0;

    listener = l;

    mRecvtimeout = recv_time;

    mPipe = createPipe();
    mPipe->init();

    mStatus = createAtomicInteger(ClientWorking);
    
    /*
    struct timeval timeout={3,0};//3s
    int ret = setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));
    if(ret < 0) {
        printf("set timeout failed \n");
        return false;
    }
     */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        return false;
    }

    printf("TcpClient init trace1 \n");
    if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("connect fail,reason is %s \n",strerror(errno));
        return false;
    }
 
    epfd = epoll_create(EPOLL_SIZE);
    printf("TcpClient init trace2 \n");
    if(epfd < 0) {
        return false;
    }
 
    //addfd(epfd, sock, true);
    st(NetUtils)::addEpollFd(epfd, sock, true);
    st(NetUtils)::addEpollFd(epfd, mPipe->getReadPipe(), true);
    printf("TcpClient init end \n");
    
    return true;
}

_TcpClient::~_TcpClient() {
    if(sock != 0) {
        close(sock);
        sock = 0;
    }

    if(epfd != 0) {
        close(epfd);
        epfd = 0;
    }

    mPipe->writeTo(createByteArray(1));
}

int _TcpClient::send(ByteArray data) {
    return st(NetUtils)::sendTcpPacket(sock,data);
}

void _TcpClient::start() {
    if(mTcpClientThread == nullptr) {
        printf("Tcpclient start \n");
        mTcpClientThread = createTcpClientThread(sock,epfd,listener,mPipe,mStatus,mRecvtimeout);
        mTcpClientThread->start();
    }
}

void _TcpClient::wait() {
    printf("wait,mTcpClientThread status is %d \n",mTcpClientThread->getStatus());
    if(mTcpClientThread == nullptr) {
        return;
    }

    if(mTcpClientThread->getStatus() == ThreadStatus::ThreadRunning
       ||mTcpClientThread->getStatus() == ThreadStatus::ThreadIdle) {
        mTcpClientThread->join();
    }
}

void _TcpClient::release() {
    close(sock);
    sock = 0;
 
    if(mTcpClientThread != nullptr) {
        if(mTcpClientThread->getStatus() == ThreadStatus::ThreadRunning
           ||mTcpClientThread->getStatus() == ThreadStatus::ThreadIdle) {
            if(mStatus->get() != ClientThreadExited) {
                mStatus->set(ClientWaitingThreadExit);
            }

            mPipe->writeTo(createByteArray(1));

            while(mStatus->get() != ClientThreadExited) {
                //Do nothing
            }

            //mTcpClientThread = nullptr;
        }
    }

    close(epfd);
    epfd = 0;
}

}