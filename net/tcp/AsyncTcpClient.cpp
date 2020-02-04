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

#include "InitializeException.hpp"
#include "AsyncTcpClient.hpp"
#include "NetUtils.hpp"

#define EPOLL_SIZE 128

#define BUF_SIZE 1024*64

namespace obotcha {

_TcpClientThread::_TcpClientThread(int sock,int epfd,SocketListener l,Pipe pi,AtomicInteger status,int timeout,int buffsize) {
    mSock = sock;
    mEpfd = epfd;
    mListener = l;
    mPipe = pi;
    mStatus = status;
    mTimeOut = timeout;
    mBufferSize = buffsize;
}

void _TcpClientThread::run() {
    
    struct epoll_event events[EPOLL_SIZE];
    byte *recv_buf = (byte *)malloc(mBufferSize);
    printf("epoll run,mTimeOut is %d \n",mTimeOut);
    while(1) {
        if(mStatus->get() == ClientWaitingThreadExit) {
            mStatus->set(ClientThreadExited);
            return;
        }
        printf("epoll trace1 \n");
        int epoll_events_count = epoll_wait(mEpfd, events, EPOLL_SIZE, mTimeOut);
        if(epoll_events_count == 0) {
            mListener->onTimeout();
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

            memset(recv_buf,0,mBufferSize);
            if(events[i].data.fd == mSock) {
                printf("epoll trace3 \n");
                int ret = recv(mSock, recv_buf, mBufferSize, 0);
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
    
    if(recv_buf != nullptr) {
        free(recv_buf);
        recv_buf = nullptr;
    }
    
}

_AsyncTcpClient::_AsyncTcpClient(String ip,int port,int recv_time,SocketListener l,int buffsize) {
    if(!init(ip,port,recv_time,l,buffsize)) {
        throw InitializeException(createString("AsyncTcpClient init failed"));
    }
}

_AsyncTcpClient::_AsyncTcpClient(String ip,int port,SocketListener l,int buffsize) {
    if(!init(ip,port,-1,l,buffsize)) {
        throw InitializeException(createString("AsyncTcpClient init failed"));
    }
}

_AsyncTcpClient::_AsyncTcpClient(int port,int recv_time,SocketListener l,int buffsize) {
    in_addr_t ip = htonl(INADDR_ANY);
    String ipString =  createString(inet_ntoa(*((struct in_addr*)&ip)));
    if(!init(ipString,port,recv_time,l,buffsize)) {
        throw InitializeException(createString("AsyncTcpClient init failed"));
    }
}
    
_AsyncTcpClient::_AsyncTcpClient(int port,SocketListener l,int buffsize) {
    in_addr_t ip = htonl(INADDR_ANY);
    String ipString =  createString(inet_ntoa(*((struct in_addr*)&ip)));
    init(ipString,port,-1,l,buffsize);
}

bool _AsyncTcpClient::init(String ip,int port,int recv_time,SocketListener l,int buffsize) {

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    std::cout << "Connect Server: " << ip->toChars() << " : " << port << endl;
    epfd = -1;
    sock = -1;

    listener = l;

    mRecvtimeout = recv_time;
    mBuffSize = buffsize;

    mPipe = createPipe();
    mPipe->init();

    mStatus = createAtomicInteger(ClientWorking);
    
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
    st(NetUtils)::addEpollFd(epfd, sock, false);
    st(NetUtils)::addEpollFd(epfd, mPipe->getReadPipe(), false);
    printf("TcpClient init end \n");
    
    return true;
}

_AsyncTcpClient::~_AsyncTcpClient() {
    release();
}

int _AsyncTcpClient::send(ByteArray data) {
    return st(NetUtils)::sendTcpPacket(sock,data);
}

void _AsyncTcpClient::start() {
    if(mTcpClientThread == nullptr) {
        printf("Tcpclient start \n");
        mTcpClientThread = createTcpClientThread(sock,epfd,listener,mPipe,mStatus,mRecvtimeout,mBuffSize);
        mTcpClientThread->start();
    }
}

void _AsyncTcpClient::wait() {
    printf("wait,mTcpClientThread status is %d \n",mTcpClientThread->getStatus());
    if(mTcpClientThread == nullptr) {
        return;
    }

    if(mTcpClientThread->getStatus() == ThreadStatus::ThreadRunning
       ||mTcpClientThread->getStatus() == ThreadStatus::ThreadIdle) {
        mTcpClientThread->join();
    }
}

void _AsyncTcpClient::release() {
    
    if(mStatus->get() == ClientWaitingThreadExit || mStatus->get() == ClientThreadExited){
        return;
    }
    
    if(sock != -1) {
        close(sock);
        sock = -1;
    }
    
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

    if(epfd != -1) {
        close(epfd);
        epfd = -1;
    }
    
}

}