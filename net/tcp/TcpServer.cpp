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
#include "Enviroment.hpp"


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

void _TcpServerThread::setRcvBuffSize(int s) {
    mBuffSize = s;
}

void _TcpServerThread::run() {
    const int EPOLL_SIZE = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerEpollSize);
    struct epoll_event events[EPOLL_SIZE];
    
    while(1) {
        //printf("TcpServer start \n");
        if(mStatus->get() == ServerWaitingThreadExit) {
            mStatus->set(ServerThreadExited);
            return;
        } else {
            mStatus->set(ServerWorking);
        }
        
        int epoll_events_count = epoll_wait(mEpollfd, events, EPOLL_SIZE, -1);
        //printf("TcpServer trace1 \n");
        if(epoll_events_count < 0) {
            mStatus->set(ServerThreadExited);
            return;
        }

        //std::cout << "epoll_events_count =" << epoll_events_count << endl;

        for(int i = 0; i < epoll_events_count; ++i) {
            int sockfd = events[i].data.fd;
            int event = events[i].events;

            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                //printf("wangsl,mPipe event is %x \n",event);
                if(mStatus->get() == ServerWaitingThreadExit) {
                    mStatus->set(ServerThreadExited);
                    //printf("wangsl,mPipe exit \n");
                    return;
                }
                
                continue;
            }

            if(((event & EPOLLIN) != 0) 
            && ((event & EPOLLRDHUP) != 0)) {
                //printf("hangup sockfd!!!!,sockefd is %d \n",sockfd);
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

                mListener->onConnect(clientfd,
                                    createString(inet_ntoa(client_address.sin_addr)),
                                    ntohs(client_address.sin_port));
            }
            else {
                byte recv_buf[mBuffSize];
                memset(recv_buf,0,mBuffSize);
                
                int len = recv(sockfd, recv_buf, mBuffSize, 0);
                if(len == 0 || len == -1) {
                    //this sockfd maybe closed!!!!!
                    //printf("tcpserver error len is %d,sockfd is %d \n",len,sockfd);
                    continue;
                }
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
    mClients->insertLast(createInteger(fd));
}

void _TcpServerThread::removeClientFd(int fd) {
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

_TcpServer::_TcpServer(int port,SocketListener l):_TcpServer{nullptr,port,l} {
    
}

_TcpServer::_TcpServer(String ip,int port,SocketListener l):
           _TcpServer{ip,
                      port,
                      st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerRcvBuffSize),
                      st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerClientNums),
                      l}{
    
}

_TcpServer::_TcpServer(String ip,int port,int rcvBuffsize,int connectionsNum,SocketListener l) {

    String reason;
    const int EPOLL_SIZE = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerEpollSize);
    if(l == nullptr) {
        throw InitializeException(createString("SocketListener is null"));
    }

    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(port);
    if(ip != nullptr) {
        serverAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    } else {
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    
    while(1) {
        printf("_TcpServer trace1 \n");
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
        printf("_TcpServer trace2 \n");
        if(sock < 0) {
            printf("_TcpServer trace3 \n");
            reason = createString("Sock Create Fail");
            break;
        }
        epfd = epoll_create(EPOLL_SIZE);
        if(epfd < 0) {
            printf("_TcpServer trace4 \n");
            reason = createString("Epoll Create Fail");
            break;
        }
        printf("_TcpServer trace5 \n");
        mServerThread = createTcpServerThread(sock,epfd,mStatus,mPipe,l,mClients,mClientsMutex,mRcvBuffSize);
        return;
    }
    
    throw InitializeException(reason);

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
    printf("_TcpServer start \n");
    
    int result = connect();
    if(result != 0) {
        printf("_TcpServer trace1 \n");
        mStatus->set(ServerThreadExited);
        return result;
    }

    mServerThread->start();

    while(mStatus->get() == ServerNotStart) {
        //TODO Nothing
    }
    printf("_TcpServer trace2 \n");
    return 0;
}

void _TcpServer::release() {

    if(mStatus->get() == ServerThreadExited || mStatus->get() == ServerWaitingThreadExit) {
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

    //start to notify server thread exit;
    if(mStatus->get() != ServerNotStart) {
        if(mStatus->get() != ServerThreadExited) {
            mStatus->set(ServerWaitingThreadExit);
        }

        mPipe->writeTo(createByteArray(1));
    
        while(mStatus->get() != ServerThreadExited) {
            //TODO
        }
    }

    if(epfd != 0) {
        close(epfd);
        epfd = 0;
    }
}

int _TcpServer::send(int fd,ByteArray data) {
    //printf("send data is %s \n",data->toValue());
    return st(NetUtils)::sendTcpPacket(fd,data);
}

void _TcpServer::setRcvBuffSize(int size) {
    mRcvBuffSize = size;
    mServerThread->setRcvBuffSize(mRcvBuffSize);
}

int _TcpServer::getRcvBuffSize() {
    return mRcvBuffSize;
}

_TcpServer::~_TcpServer() {
    release();
}

}