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

#include "AsyncLocalSocketClient.hpp"
#include "NetUtils.hpp"

#define EPOLL_SIZE 128

#define BUF_SIZE 1024*64

namespace obotcha {

_AsyncLocalSocketClientThread::_AsyncLocalSocketClientThread(int sock,
                                                             int epfd,
                                                             SocketListener l,
                                                             Pipe pi,
                                                             AtomicInteger status,
                                                             int timeout,
                                                             int buffersize) {
    mSock = sock;
    mEpfd = epfd;
    mListener = l;
    mPipe = pi;
    mStatus = status;
    mTimeOut = timeout;
    mBufferSize = buffersize;
}

void _AsyncLocalSocketClientThread::run() {
    
    struct epoll_event events[EPOLL_SIZE];
    char *recv_buf = (char *)malloc(mBufferSize);
    printf("epoll run,mTimeOut is %d \n",mTimeOut);
    while(1) {
        if(mStatus->get() == LocalSocketClientWaitingThreadExit) {
            mStatus->set(LocalSocketClientThreadExited);
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

            memset(recv_buf,0,mBufferSize);
            if(events[i].data.fd == mSock) {
                printf("epoll trace3 \n");
                int ret = recv(mSock, recv_buf, mBufferSize, 0);
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

    free(recv_buf);
}

_AsyncLocalSocketClient::_AsyncLocalSocketClient(String domain,SocketListener l,int recvtime,int buffsize) {

    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars()); 

    listener = l;

    mPipe = createPipe();
    mPipe->init();

    mStatus = createAtomicInteger(LocalSocketClientWorking);

    epfd = epoll_create(EPOLL_SIZE);

    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    mRecvtimeout = recvtime;

    mBuffSize = buffsize;
}

bool _AsyncLocalSocketClient::init() {
    printf("TcpClient init start \n");
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);  
    printf("LocalSocketClient init trace3 \n");
    if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("connect error :%s \n",strerror(errno));
        return false;
    }
    printf("LocalSocketClient init trace4 \n");

    st(NetUtils)::addEpollFd(epfd, sock,false);
    st(NetUtils)::addEpollFd(epfd, mPipe->getReadPipe(), false);
    return true;
}

int _AsyncLocalSocketClient::send(ByteArray data) {
    return st(NetUtils)::sendTcpPacket(sock,data);
}

void _AsyncLocalSocketClient::start() {
    if(mAsyncLocalSocketClientThread == nullptr) {
        init();
        mAsyncLocalSocketClientThread = createAsyncLocalSocketClientThread(sock,epfd,listener,mPipe,mStatus,mRecvtimeout,mBuffSize);
        mAsyncLocalSocketClientThread->start();
    }
}

void _AsyncLocalSocketClient::wait() {
    printf("wait,mTcpClientThread status is %d \n",mAsyncLocalSocketClientThread->getStatus());
    if(mAsyncLocalSocketClientThread == nullptr) {
        return;
    }

    if(mAsyncLocalSocketClientThread->getStatus() == ThreadStatus::ThreadRunning
       ||mAsyncLocalSocketClientThread->getStatus() == ThreadStatus::ThreadIdle) {
        mAsyncLocalSocketClientThread->join();
    }
}

void _AsyncLocalSocketClient::release() {
    if(mStatus->get() == LocalSocketClientWaitingThreadExit || mStatus->get() == LocalSocketClientThreadExited){
        return;
    }
    
    if(sock != -1) {
        close(sock);
        sock = -1;
    }
    
    if(mAsyncLocalSocketClientThread != nullptr) {
        if(mAsyncLocalSocketClientThread->getStatus() == ThreadStatus::ThreadRunning
           ||mAsyncLocalSocketClientThread->getStatus() == ThreadStatus::ThreadIdle) {
            if(mStatus->get() != LocalSocketClientThreadExited) {
                mStatus->set(LocalSocketClientWaitingThreadExit);
            }

            mPipe->writeTo(createByteArray(1));

            while(mStatus->get() != LocalSocketClientThreadExited) {
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

 _AsyncLocalSocketClient::~_AsyncLocalSocketClient() {
     release();
 }

}