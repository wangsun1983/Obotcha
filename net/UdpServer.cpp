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
#include <errno.h>

#include "AutoMutex.hpp"
#include "UdpServer.hpp"
#include "Pipe.hpp"
#include "NetUtils.hpp"
#include "AutoMutex.hpp"

#define EPOLL_SIZE 1024*8

#define BUFF_SIZE 1024*64

namespace obotcha {

_UdpServerThread::_UdpServerThread(int sock,
                    int epfd,
                    AtomicInteger status,
                    Pipe pi,
                    SocketListener listener,
                    ArrayList<Integer> clients,
                    Mutex mutex) {

    mSocket = sock;
    mEpollfd = epfd;
    mStatus = status;
    mPipe = pi;
    mListener = listener;
    mClients = clients;
    mClientMutex = mutex;
}

void _UdpServerThread::run() {
    struct epoll_event events[EPOLL_SIZE];
    char recv_buf[BUFF_SIZE];

    while(1) {
        printf("UdpServer start \n");
        if(mStatus->get() == UdpServerWaitingThreadExit) {
            mStatus->set(UdpServerThreadExited);
            printf("UdpServer exit111 \n");
            return;
        }

        printf("UdpServer trace0 mEpollfd is %d \n",mEpollfd);
        int epoll_events_count = epoll_wait(mEpollfd, events, EPOLL_SIZE, -1);
        printf("UdpServer trace1 \n");
        if(epoll_events_count < 0) {
            mStatus->set(UdpServerThreadExited);
            printf("UdpServer trace2 \n");
            return;
        }
 
        std::cout << "epoll_events_count =" << epoll_events_count << endl;

        for(int i = 0; i < epoll_events_count; ++i) {
            int sockfd = events[i].data.fd;
            int event = events[i].events;
            printf("wangsl,sockfd %d,mSocket is %d \n",sockfd,mSocket);
            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                printf("wangsl,mPipe event is %x \n",event);
                if(mStatus->get() == UdpServerWaitingThreadExit) {
                    mStatus->set(UdpServerThreadExited);
                    printf("wangsl,mPipe exit \n");
                    return;
                }
                
                continue;
            }

            if(sockfd == mSocket) {
                printf("udpserver trace3 \n");
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                                
                int size = recvfrom(sockfd,
                                   recv_buf,
                                   sizeof(recv_buf),
                                   0,
                                   (struct sockaddr *)&client_address,
                                   &client_addrLength);
                printf("udpserver trace4,size is %d \n",size);
                ByteArray pack = createByteArray(recv_buf,size);
                if(mListener != nullptr) {
                    printf("udpserver trace5 \n");
                    mListener->onAccept(sockfd,
                                           createString(inet_ntoa(client_address.sin_addr)),
                                           ntohs(client_address.sin_port),
                                           pack);
                }

                //mListener->onConnect(clientfd,
                //                    createString(inet_ntoa(client_address.sin_addr)),
                //                    ntohs(client_address.sin_port));
            }
            //else {
                
            //    int len = recv(sockfd, recv_buf, BUFF_SIZE, 0);
            //    ByteArray pack = createByteArray(recv_buf,len);
            //    if(mListener != nullptr) {
            //        mListener->onAccept(sockfd,pack);
            //    }
            //}
            //addfd(epfd, sockfd, true);
        }
      
    }

    printf("thread exit!!!!! \n");
    mStatus->set(UdpServerThreadExited);
}

void _UdpServerThread::addClientFd(int fd) {
    AutoMutex l(mClientMutex);
    mClients->insertLast(fd);
}

void _UdpServerThread::removeClientFd(int fd) {
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

_UdpServer::_UdpServer(int port,SocketListener l) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    mPipe = createPipe();
    mPipe->init();

    sock = 0;
    epfd = 0;

    mListener = l;

    mClientsMutex = createMutex("UdpServer");

    mStatus = createAtomicInteger(UdpServerWorking);

    mClients = createArrayList<Integer>();

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    epfd = epoll_create(EPOLL_SIZE);

    mServerThread = createUdpServerThread(sock,epfd,mStatus,mPipe,l,mClients,mClientsMutex);
}

_UdpServer::_UdpServer(String ip,int port,SocketListener l) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());

    mPipe = createPipe();
    mPipe->init();

    sock = 0;
    epfd = 0;

    mListener = l;

    mStatus = createAtomicInteger(UdpServerWorking);

    mClients = createArrayList<Integer>();
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    epfd = epoll_create(EPOLL_SIZE);

    mServerThread = createUdpServerThread(sock,epfd,mStatus,mPipe,l,mClients,mClientsMutex);
}

int _UdpServer::connect() {
    int opt = SO_REUSEADDR;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    if( bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("bind server faild , error = %s \n", strerror(errno));
        return -UdpServerBindFailed;
    }
    printf("sock is %d \n",sock);

    //int ret = listen(sock, 5);
    //if(ret < 0) {
    //    printf("list error is %s \n",strerror(errno));
    //    return -UdpServerListenFailed;
    //}

    //add epoll
    printf("UdpServer connect \n");
    st(NetUtils)::addEpollFd(epfd,sock,true);
    st(NetUtils)::addEpollFd(epfd,mPipe->getReadPipe(),true);

    return 0;
}

int _UdpServer::start() {
    
    int result = connect();
    if(result != 0) {
        mStatus->set(UdpServerThreadExited);
        return result;
    }

    mServerThread->start();

    return 0;
}

void _UdpServer::release() {
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
    if(mStatus->get() != UdpServerThreadExited) {
        mStatus->set(UdpServerWaitingThreadExit);
    }

    mPipe->writeTo(createByteArray(1));

    while(mStatus->get() != UdpServerThreadExited) {
        //TODO nothing
    }
    printf("release end \n");
}

int _UdpServer::send(String ip,int port,ByteArray data) {
    return st(NetUtils)::sendUdpPacket(sock,ip,port,data);
}

_UdpServer::~_UdpServer() {
    release();
}

}