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
#include "TcpServer.hpp"
#include "Pipe.hpp"
#include "NetUtils.hpp"
#include "AutoMutex.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"


#define EPOLL_SIZE 1024*8

#define gDefaultRcvBuffSize 1024*64

#define gDefaultClientNums 1024*64

namespace obotcha {

_TcpServerThread::_TcpServerThread(int sock,
                    int epfd,
                    AtomicInteger status,
                    Pipe pi,
                    SocketListener listener,
                    ArrayList<Integer> clients,
                    Mutex mutex,
                    int buffsize) {

    mSocket = sock;
    mEpollfd = epfd;
    mStatus = status;
    mPipe = pi;
    mListener = listener;
    mClients = clients;
    mClientMutex = mutex;

    mBuffSize = buffsize;
}

int _TcpServerThread::setRcvBuffSize(int s) {
    mBuffSize = s;
}

void _TcpServerThread::run() {
    struct epoll_event events[EPOLL_SIZE];

    while(1) {
        printf("TcpServer start \n");
        if(mStatus->get() == ServerWaitingThreadExit) {
            mStatus->set(ServerThreadExited);
            return;
        } else {
            mStatus->set(ServerWorking);
        }

        int epoll_events_count = epoll_wait(mEpollfd, events, EPOLL_SIZE, -1);
        printf("TcpServer trace1 \n");
        if(epoll_events_count < 0) {
            mStatus->set(ServerThreadExited);
            return;
        }

        std::cout << "epoll_events_count =" << epoll_events_count << endl;

        for(int i = 0; i < epoll_events_count; ++i) {
            int sockfd = events[i].data.fd;
            int event = events[i].events;

            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                printf("wangsl,mPipe event is %x \n",event);
                if(mStatus->get() == ServerWaitingThreadExit) {
                    mStatus->set(ServerThreadExited);
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
 
                //std::cout << "client connection from: "
                //     << inet_ntoa(client_address.sin_addr) << ":"
                //     << ntohs(client_address.sin_port) << ", clientfd = "
                //     << clientfd << endl;
 
                st(NetUtils)::addEpollFd(mEpollfd, clientfd, true);

                addClientFd(clientfd);

                mListener->onConnect(clientfd,
                                    createString(inet_ntoa(client_address.sin_addr)),
                                    ntohs(client_address.sin_port));
            }
            else {
                char recv_buf[mBuffSize];
                int len = recv(sockfd, recv_buf, mBuffSize, 0);
                ByteArray pack = createByteArray(&recv_buf[0],len);
                if(mListener != nullptr) {
                    mListener->onAccept(sockfd,nullptr,-1,pack);
                }
            }
        }
      
    }

    mStatus->set(ServerThreadExited);
}

void _TcpServerThread::addClientFd(int fd) {
    AutoMutex l(mClientMutex);
    mClients->insertLast(fd);
}

void _TcpServerThread::removeClientFd(int fd) {
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

_TcpServer::_TcpServer(int port,SocketListener l):_TcpServer{nullptr,port,l} {
    
}

_TcpServer::_TcpServer(String ip,int port,SocketListener l):_TcpServer{ip,port,gDefaultRcvBuffSize,gDefaultClientNums,l}{
    
}

_TcpServer::_TcpServer(String ip,int port,int rcvBuffsize,int connectionsNum,SocketListener l) {

    String reason;

    if(l == nullptr) {
        throw createInitializeException(createString("SocketListener is null"));
    }

    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(port);
    if(ip != nullptr) {
        serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    } else {
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    
    while(1) {
        mPipe = createPipe();
        if(mPipe->init() == -1) {
            break;
        }

        mRcvBuffSize = rcvBuffsize;

        mConnectionNum = connectionsNum;

        sock = 0;

        epfd = 0;

        mListener = l;
        mClientsMutex = createMutex("TcpServer");

        mStatus = createAtomicInteger(ServerNotStart);
        mClients = createArrayList<Integer>();
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0) {
            reason = createString("Sock Create Fail");
            break;
        }
        epfd = epoll_create(EPOLL_SIZE);
        if(epfd < 0) {
            reason = createString("Epoll Create Fail");
            break;
        }

        mServerThread = createTcpServerThread(sock,epfd,mStatus,mPipe,l,mClients,mClientsMutex,mRcvBuffSize);
        return;
    }
    
    throw createInitializeException(reason);

}

int _TcpServer::removeClientFd(int fd) {
    return st(NetUtils)::delEpollFd(epfd,fd);
}

int _TcpServer::addClientFd(int fd) {
    return st(NetUtils)::addEpollFd(epfd,fd,true);
}

int _TcpServer::getStatus() {
    return mStatus->get();
}

int _TcpServer::getTcpEpollfd() {
    return epfd;
}

int _TcpServer::connect() {
    int opt = 1;
    
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
        return -AttributeSetFail;
    }

    if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        return -NetBindFail;
    }

    int ret = listen(sock, mConnectionNum);
    if(ret < 0) {
        return -NetListenFail;
    }

    //add epoll
    if(st(NetUtils)::addEpollFd(epfd,sock,true) < 0) {
        return -WriteFail;
    }

    if(st(NetUtils)::addEpollFd(epfd,mPipe->getReadPipe(),true) < 0) {
        return -WriteFail;
    }

    return 0;
}

int _TcpServer::start() {
    
    int result = connect();
    if(result != 0) {
        mStatus->set(ServerThreadExited);
        return result;
    }

    mServerThread->start();

    return 0;
}

void _TcpServer::release() {   
    if(sock != 0) {
        close(sock);
        sock = 0;
    }
    
    if(epfd != 0) {
        close(epfd);
        epfd = 0;
    }
    
    {
        AutoMutex l(mClientsMutex);
        int size = mClients->size();
        for(int index = 0;index < size;index++) {
            int fd = mClients->get(index)->toValue();
            close(fd);
        }
    }

    //start to notify server thread exit;
    if(mStatus->get() != ServerNotStart) {
        if(mStatus->get() != ServerThreadExited) {
            mStatus->set(ServerWaitingThreadExit);
        }

        mPipe->writeTo(createByteArray(1));
    
        while(mStatus->get() != ServerThreadExited) {
            //TODO nothing
        }
    }
}

int _TcpServer::send(int fd,ByteArray data) {
    printf("send data is %s \n",data->toValue());
    return st(NetUtils)::sendTcpPacket(fd,data);
}

int _TcpServer::setRcvBuffSize(int size) {
    mRcvBuffSize = size;
}

_TcpServer::~_TcpServer() {
    release();
}

}