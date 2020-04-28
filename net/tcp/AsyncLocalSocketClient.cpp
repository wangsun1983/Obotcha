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
    recvBuff = nullptr;
}

_AsyncLocalSocketClientThread::~_AsyncLocalSocketClientThread() {
    if(recvBuff != nullptr) {
        free(recvBuff);
        recvBuff = nullptr;
    }
}

void _AsyncLocalSocketClientThread::run() {
    
    struct epoll_event events[EPOLL_SIZE];
    recvBuff = (byte *)malloc(mBufferSize);
    while(1) {
        if(mStatus->get() == LocalSocketClientWaitingThreadExit) {
            mStatus->set(LocalSocketClientThreadExited);
            return;
        }
        int epoll_events_count = epoll_wait(mEpfd, events, EPOLL_SIZE, mTimeOut);
        if(epoll_events_count == 0) {
            mListener->onTimeout();
            return;
        } else if(epoll_events_count < 0) {
            return;
        }

        for(int i = 0; i < epoll_events_count ; ++i) {

            int sockfd = events[i].data.fd;
            int event = events[i].events;

            if(((event&EPOLLIN) != 0) 
            && ((event &EPOLLRDHUP) != 0)) {
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
                if(mStatus->get() == LocalSocketClientWaitingThreadExit) {
                    mStatus->set(LocalSocketClientThreadExited);
                    return;
                }
                
                continue;
            }

            memset(recvBuff,0,mBufferSize);
            if(events[i].data.fd == mSock) {
                int ret = recv(mSock, recvBuff, mBufferSize, 0);
                if(ret == 0) {
                    st(NetUtils)::delEpollFd(mEpfd,sockfd);
                    mListener->onDisconnect(sockfd);
                    close(sockfd);
                    mStatus->set(LocalSocketClientThreadExited);
                    return;
                } else {
                    ByteArray pack = createByteArray(recvBuff,ret);
                    mListener->onAccept(mSock,nullptr,-1,pack);
                }
            }
        }
    }
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
    //int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);  
    if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        return false;
    }
    
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
    if(mAsyncLocalSocketClientThread == nullptr) {
        return;
    }

    if(mAsyncLocalSocketClientThread->getStatus() == st(Thread)::Running
       ||mAsyncLocalSocketClientThread->getStatus() == st(Thread)::Idle) {
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
        if(mAsyncLocalSocketClientThread->getStatus() == st(Thread)::Running
           ||mAsyncLocalSocketClientThread->getStatus() == st(Thread)::Idle) {
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