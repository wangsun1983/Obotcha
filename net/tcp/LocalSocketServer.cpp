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
#include "Error.hpp"
#include "InitializeException.hpp"

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
                    String domain,
                    int buffsize) {

    mSocket = sock;
    mEpollfd = epfd;
    mStatus = status;
    mPipe = pi;
    mListener = listener;
    mClients = clients;
    mClientMutex = mutex;
    mDomain = domain;
    mBuffSize = buffsize;
}

void _LocalSocketServerThread::setRcvBuffSize(int s) {
    mBuffSize = s;
}

void _LocalSocketServerThread::run() {
    struct epoll_event events[EPOLL_SIZE];

    while(1) {
        if(mStatus->get() == LocalServerWaitingThreadExit) {
            mStatus->set(LocalServerThreadExited);
            return;
        } else {
            mStatus->set(LocalServerWorking);
        }

        int epoll_events_count = epoll_wait(mEpollfd, events, EPOLL_SIZE, -1);
        if(epoll_events_count < 0) {
            mStatus->set(LocalServerThreadExited);
            return;
        }

        for(int i = 0; i < epoll_events_count; ++i) {
            int sockfd = events[i].data.fd;
            int event = events[i].events;

            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                if(mStatus->get() == LocalServerWaitingThreadExit) {
                    mStatus->set(LocalServerThreadExited);
                    return;
                }
                
                continue;
            }

            if(((event & EPOLLIN) != 0) 
            && ((event & EPOLLRDHUP) != 0)) {
                epoll_ctl(mEpollfd, EPOLL_CTL_DEL, sockfd, NULL);
                st(NetUtils)::delEpollFd(mEpollfd,sockfd);
                removeClientFd(sockfd);
                mListener->onDisconnect(sockfd);
                close(sockfd);
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

                mListener->onConnect(clientfd,mDomain);
            }
            else {
                byte recv_buf[mBuffSize];
                memset(recv_buf,0,mBuffSize);
                
                int len = recv(sockfd, recv_buf, mBuffSize, 0);
                if(len == 0 || len == -1) {
                    //this sockfd maybe closed!!!!!
                    continue;
                }
                ByteArray pack = createByteArray(&recv_buf[0],len);
                if(mListener != nullptr) {
                    mListener->onAccept(sockfd,nullptr,-1,pack);
                }
            }
        }
      
    }

    mStatus->set(LocalServerThreadExited);
}

void _LocalSocketServerThread::addClientFd(int fd) {
    AutoMutex l(mClientMutex);
    mClients->insertLast(createInteger(fd));
}

void _LocalSocketServerThread::removeClientFd(int fd) {
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

_LocalSocketServer::_LocalSocketServer(String domain,SocketListener l,int clients,int recvsize) {
    String reason;

    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, domain->toChars());  
    
    while(1) {
        mPipe = createPipe();
        if(mPipe->init() == -1) {
            break;
        }

        mClientsNum = clients;

        mListener = l;

        mClientsMutex = createMutex("LocalSocketServer");

        mStatus = createAtomicInteger(LocalServerNotStart);

        mClients = createArrayList<Integer>();

        sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if(sock < 0) {
            reason = createString("Sock Create Fail");
            break;
        }
    
        epfd = epoll_create(EPOLL_SIZE);
        if(epfd < 0) {
            reason = createString("Epoll Create Fail");
            break;
        }

        mServerThread = createLocalSocketServerThread(sock,
                                                epfd,
                                                mStatus,
                                                mPipe,
                                                l,
                                                mClients,
                                                mClientsMutex,
                                                domain,
                                                recvsize);

        mDomain = domain;
        return;
    }

    throw InitializeException(reason);
}

int _LocalSocketServer::getStatus() {
    return mStatus->get();
}

int _LocalSocketServer::connect() {
    
    unlink(mDomain->toChars());

    int len = offsetof(struct sockaddr_un, sun_path) + strlen(serverAddr.sun_path);   

    if( bind(sock, (struct sockaddr *)&serverAddr, len) < 0) {
        return -NetBindFail;
    }

    int ret = listen(sock, mClientsNum);

    if(ret < 0) {
        return -NetListenFail;
    }
    //add epoll
    if(st(NetUtils)::addEpollFd(epfd,sock,false) < 0) {
        return -WriteFail;
    }

    if(st(NetUtils)::addEpollFd(epfd,mPipe->getReadPipe(),false) < 0) {
        return -WriteFail;
    };

    return 0;
}

int _LocalSocketServer::start() {
    
    int result = connect();
    if(result != 0) {
        mStatus->set(LocalServerThreadExited);
        return result;
    }

    mServerThread->start();

    while(mStatus->get() == LocalServerNotStart) {
        //TODO Nothing
    }

    return 0;
}

void _LocalSocketServer::release() {
    if(mStatus->get() == LocalServerThreadExited || mStatus->get() == LocalServerWaitingThreadExit) {
        return;
    }

    if(sock >= 0) {
        close(sock);
        sock = -1;
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
    if(mStatus->get() != LocalServerNotStart) {
        if(mStatus->get() != LocalServerThreadExited) {
            mStatus->set(LocalServerWaitingThreadExit);
        }

        mPipe->writeTo(createByteArray(1));
    
        while(mStatus->get() != LocalServerThreadExited) {
            //TODO
        }
    }

    if(epfd >= 0) {
        close(epfd);
        epfd = -1;
    }

}

int _LocalSocketServer::send(int fd,ByteArray data) {
    return st(NetUtils)::sendTcpPacket(fd,data);
}

void _LocalSocketServer::setRcvBuffSize(int size) {
    mServerThread->setRcvBuffSize(size);
}

_LocalSocketServer::~_LocalSocketServer() {
    release();
}

}