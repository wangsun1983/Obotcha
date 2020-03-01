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
#include "Error.hpp"
#include "Byte.hpp"

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
    byte recv_buf[BUFF_SIZE];

    memset(events,0,sizeof(struct epoll_event) * EPOLL_SIZE);
    memset(recv_buf,0,BUFF_SIZE);

    while(1) {
        if(mStatus->get() == UdpServerWaitingThreadExit) {
            mStatus->set(UdpServerThreadExited);
            return;
        } else {
            mStatus->set(UdpServerWorking);
        }

        int epoll_events_count = epoll_wait(mEpollfd, events, EPOLL_SIZE, -1);
        if(epoll_events_count < 0) {
            mStatus->set(UdpServerThreadExited);
            return;
        }

        for(int i = 0; i < epoll_events_count; ++i) {
            int sockfd = events[i].data.fd;
            int event = events[i].events;
            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                if(mStatus->get() == UdpServerWaitingThreadExit) {
                    mStatus->set(UdpServerThreadExited);
                    return;
                }
                
                continue;
            }

            

            if(sockfd == mSocket) {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                                
                int size = recvfrom(sockfd,
                                   recv_buf,
                                   sizeof(recv_buf),
                                   0,
                                   (struct sockaddr *)&client_address,
                                   &client_addrLength);
                ByteArray pack = createByteArray(recv_buf,size);
                if(mListener != nullptr) {
                    mListener->onAccept(sockfd,
                                           createString(inet_ntoa(client_address.sin_addr)),
                                           ntohs(client_address.sin_port),
                                           pack);
                }

            }
        }
      
    }

    mStatus->set(UdpServerThreadExited);
}

void _UdpServerThread::addClientFd(int fd) {
    AutoMutex l(mClientMutex);
    mClients->insertLast(createInteger(fd));
}

void _UdpServerThread::removeClientFd(int fd) {
    AutoMutex l(mClientMutex);
    int size = mClients->size();
    
    for(int index = 0;index<size;index++) {
        if(mClients->get(index)->toValue() == fd) {
            mClients->removeAt(index);
            close(fd);
            return;
        }
    }
}

_UdpServer::_UdpServer(int port,SocketListener l):_UdpServer{nullptr,port,l} {

}

_UdpServer::_UdpServer(String ip,int port,SocketListener l) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if(ip == nullptr) {
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    }

    mPipe = createPipe();
    mPipe->init();

    sock = 0;
    epfd = 0;

    mListener = l;

    mStatus = createAtomicInteger(UdpServerIdle);

    mClientsMutex = createMutex(createString("UdpServerMutex"));

    mClients = createArrayList<Integer>();
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    epfd = epoll_create(EPOLL_SIZE);

    mServerThread = createUdpServerThread(sock,epfd,mStatus,mPipe,l,mClients,mClientsMutex);
}

int _UdpServer::connect() {
    int opt = SO_REUSEADDR;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    if( bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        return -NetBindFail;
    }
    
    //add epoll
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

    while(mStatus->get() == UdpServerIdle) {
        //TODO Nothing
    }

    return 0;
}

void _UdpServer::release() {
    if(mStatus->get() == UdpServerThreadExited || mStatus->get() == UdpServerWaitingThreadExit) {
        return;
    }

    if(sock != 0) {
        close(sock);
        sock = 0;
    }

    {
        AutoMutex l(mClientsMutex);
        int size = mClients->size();
        for(int index = 0;index < size;index++) {
            int fd = mClients->get(index)->toValue();
            close(fd);
        }
    }
    
    if(mStatus->get() != UdpServerIdle) {
        if(mStatus->get() != UdpServerThreadExited) {
            mStatus->set(UdpServerWaitingThreadExit);
        }
        mPipe->writeTo(createByteArray(1));

        while(mStatus->get() != UdpServerThreadExited) {
            //TODO nothing
        }
    }


    close(epfd);
}

//int _UdpServer::send(String ip,int port,ByteArray data) {
//    return st(NetUtils)::sendUdpPacket(sock,ip,port,data);
//}

_UdpServer::~_UdpServer() {
    release();
}

}