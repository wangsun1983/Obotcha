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

#include "AutoMutex.hpp"
#include "LocalSocketServer.hpp"
#include "Pipe.hpp"
#include "NetUtils.hpp"
#include "AutoMutex.hpp"


#define EPOLL_SIZE 1024*8

#define BUFF_SIZE 1024*64

namespace obotcha {

_LocalSocketServerThread::_LocalSocketServerThread(int sock,
                    int epfd,
                    AtomicInteger status,
                    Pipe pi,
                    SocketListener listener,
                    ArrayList<Integer> clients,
                    Mutex mutex,
                    String domain) {

    mSocket = sock;
    mEpollfd = epfd;
    mStatus = status;
    mPipe = pi;
    mListener = listener;
    mClients = clients;
    mClientMutex = mutex;
    mDomain = domain;
}

void _LocalSocketServerThread::run() {
    struct epoll_event events[EPOLL_SIZE];

    while(1) {
        printf("TcpServer start \n");
        if(mStatus->get() == LocalServerWaitingThreadExit) {
            mStatus->set(LocalServerThreadExited);
            printf("TcpServer exit111 \n");
            return;
        }

        int epoll_events_count = epoll_wait(mEpollfd, events, EPOLL_SIZE, -1);
        printf("TcpServer trace1 \n");
        if(epoll_events_count < 0) {
            mStatus->set(LocalServerThreadExited);
            printf("TcpServer trace2 \n");
            return;
        }
 
        std::cout << "epoll_events_count =" << epoll_events_count << endl;

        for(int i = 0; i < epoll_events_count; ++i) {
            int sockfd = events[i].data.fd;
            int event = events[i].events;

            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                printf("wangsl,mPipe event is %x \n",event);
                if(mStatus->get() == LocalServerWaitingThreadExit) {
                    mStatus->set(LocalServerThreadExited);
                    printf("wangsl,mPipe exit \n");
                    return;
                }
                
                continue;
            }

            if(((event&EPOLLIN) != 0) 
            && ((event &EPOLLRDHUP) != 0)) {
                printf("hangup sockfd!!!! \n");
                //epoll_ctl(mEpollfd, EPOLL_CTL_DEL, sockfd, NULL);
                st(NetUtils)::delEpollFd(mEpollfd,sockfd);
                removeClientFd(sockfd);
                mListener->onDisconnect(sockfd);
                continue;
            }
            
            if(sockfd == mSocket) {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                int clientfd = accept( mSocket, ( struct sockaddr* )&client_address, &client_addrLength );
 
                std::cout << "client connection from: "
                     << inet_ntoa(client_address.sin_addr) << ":"
                     << ntohs(client_address.sin_port) << ", clientfd = "
                     << clientfd << endl;
 
                st(NetUtils)::addEpollFd(mEpollfd, clientfd, true);

                addClientFd(clientfd);

                mListener->onConnect(clientfd,mDomain);
            }
            else {
                char recv_buf[BUFF_SIZE];
                int len = recv(sockfd, recv_buf, BUFF_SIZE, 0);
                ByteArray pack = createByteArray(recv_buf,len);
                if(mListener != nullptr) {
                    mListener->onAccept(sockfd,nullptr,-1,pack);
                }
            }
            //addfd(epfd, sockfd, true);
        }
      
    }

    printf("thread exit!!!!! \n");
    mStatus->set(LocalServerThreadExited);
}

void _LocalSocketServerThread::addClientFd(int fd) {
    AutoMutex l(mClientMutex);
    mClients->insertLast(fd);
}

void _LocalSocketServerThread::removeClientFd(int fd) {
    AutoMutex l(mClientMutex);
    int size = mClients->size();
    
    for(int index = 0;index<size;index++) {
        if(mClients->get(index)->toValue() == fd) {
            mClients->remove(index);
            close(fd);
            return;
        }
    }
}

_LocalSocketServer::_LocalSocketServer(String domain,SocketListener l) {

    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars());  

    mPipe = createPipe();
    mPipe->init();

    sock = 0;
    epfd = 0;

    mListener = l;

    mClientsMutex = createMutex("LocalSocketServer");

    mStatus = createAtomicInteger(LocalServerWorking);

    mClients = createArrayList<Integer>();

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    
    epfd = epoll_create(EPOLL_SIZE);

    mServerThread = createLocalSocketServerThread(sock,
                                                epfd,
                                                mStatus,
                                                mPipe,
                                                l,
                                                mClients,
                                                mClientsMutex,
                                                domain);

    mDomain = domain;
}

int _LocalSocketServer::connect() {
    int opt = 1;
    
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
    //add epoll
    st(NetUtils)::addEpollFd(epfd,sock,true);
    st(NetUtils)::addEpollFd(epfd,mPipe->getReadPipe(),true);
    printf("LocalSocketServer connect trace6 \n");

    return 0;
}

int _LocalSocketServer::start() {
    
    int result = connect();
    if(result != 0) {
        mStatus->set(LocalServerThreadExited);
        return result;
    }

    mServerThread->start();

    return 0;
}

void _LocalSocketServer::release() {
    printf("release trace 1 \n");
    close(sock);
    sock = 0;

    close(epfd);
    {
        AutoMutex l(mClientsMutex);
        int size = mClients->size();
        for(int index = 0;index < size;index++) {
            int fd = mClients->get(index)->toValue();
            close(fd);
        }
    }

    //start to notify server thread exit;
    if(mStatus->get() != LocalServerThreadExited) {
        mStatus->set(LocalServerWaitingThreadExit);
    }

    mPipe->writeTo(createByteArray(1));

    while(mStatus->get() != LocalServerThreadExited) {
        //TODO nothing
    }
    printf("release end \n");
}

int _LocalSocketServer::send(int fd,ByteArray data) {
    return st(NetUtils)::sendTcpPacket(fd,data);
}

_LocalSocketServer::~_LocalSocketServer() {
    release();
}

}