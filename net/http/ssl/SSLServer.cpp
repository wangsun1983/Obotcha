#include "SSLServer.hpp"
#include "Enviroment.hpp"
#include "InitializeException.hpp"
#include "SSLManager.hpp"

namespace obotcha {

//----------------- HttpsThread -----------------
int _SSLThread::addEpollFd(int epollfd, int fd, bool enable_et) {
    struct epoll_event ev;
    memset(&ev.data, 0, sizeof(ev.data));
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLRDHUP |EPOLLHUP;
    //if( enable_et )
    //    ev.events |= EPOLLET;
    int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0) {
        return ret;
    }
    
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)| O_NONBLOCK);
}

int _SSLThread::delEpollFd(int epollfd, int fd) {
    return epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}


_SSLThread::_SSLThread(String ip,int port,SocketListener l,String c,String k) {
    String mIp = ip;

    mCertificate = c;

    mKey = k;

    int mPort = port;

    mMutex = createMutex();
    mSocks = createHashMap<int,Socket>();


    const int EPOLL_SIZE = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerEpollSize,1024);
    if(l == nullptr) {
        throw InitializeException("SocketListener is null");
    }

    mSockAddr.sin_family = AF_INET;
    mSockAddr.sin_port = htons(port);
    if(ip != nullptr) {
        mSockAddr.sin_addr.s_addr = inet_addr(ip->toChars());
    } else {
        mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    
    while(1) {
        mPipe = createPipe();
        if(mPipe->init() == -1) {
            break;
        }

        mRcvBuffSize = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerRcvBuffSize,1024);

        mClientNums = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerClientNums,1024);

        mSocket = 0;

        mEpollfd = 0;

        mListener = l;
        
        mClientMutex = createMutex("SSLTcpServer");
        
        mSocket = socket(PF_INET, SOCK_STREAM, 0);
        if(mSocket < 0) {
            break;
        }

        mEpollfd = epoll_create(EPOLL_SIZE);
        if(mEpollfd < 0) {
            break;
        }

        int opt = 1;
    
        if(setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
            break;
        }

        if(bind(mSocket, (struct sockaddr *)&mSockAddr, sizeof(struct sockaddr)) < 0) {
            break;
        }

        int ret = listen(mSocket, mClientNums);
        if(ret < 0) {
            break;
        }

        //add epoll
        if(addEpollFd(mEpollfd,mSocket,true) < 0) {
            break;
        }

        if(addEpollFd(mEpollfd,mPipe->getReadPipe(),true) < 0) {
            break;
        }
       
        return;
    }
}

void _SSLThread::run() {
    const int EPOLL_SIZE = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerEpollSize,1024);
    struct epoll_event events[EPOLL_SIZE];
    while(1) {
        int epoll_events_count = epoll_wait(mEpollfd, events, EPOLL_SIZE, -1);
        if(epoll_events_count < 0) {
            return;
        }

         for(int i = 0; i < epoll_events_count; ++i) {
            int sockfd = events[i].data.fd;
            int event = events[i].events;

            //check whether thread need exit
            if(sockfd == mPipe->getReadPipe()) {
                return;
            }

            if(((event & EPOLLIN) != 0) 
            && ((event & EPOLLRDHUP) != 0)) {
                epoll_ctl(mEpollfd, EPOLL_CTL_DEL, sockfd, NULL);
                delEpollFd(mEpollfd,sockfd);
                //SocketResponser r = createSocketResponser(sockfd);
                Socket s = mSocks->get(sockfd);
                {
                    AutoLock l(mMutex);
                    mSocks->remove(sockfd);
                }

                //mListener->onDisconnect(s);
                mListener->onSocketMessage(st(Socket)::Disconnect,s,nullptr);
                
                st(SSLManager)::getInstance()->remove(sockfd);
                close(sockfd);
                continue;
            }
            
            if(sockfd == mSocket) {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                int clientfd = accept( mSocket, ( struct sockaddr* )&client_address, &client_addrLength );
                
                addEpollFd(mEpollfd, clientfd, true);
                
                SSLInfo ssl = createSSLInfo(mCertificate,mKey);
                if(ssl->bindSocket(clientfd) == 0) {
                    //mClients->put(clientfd,ssl);
                    st(SSLManager)::getInstance()->add(clientfd,ssl);
                    //SocketResponser r = createSocketResponser(clientfd,
                    //                                          createString(inet_ntoa(client_address.sin_addr)),
                    //                                          ntohs(client_address.sin_port));
                    Socket s = createSocket(clientfd);
                    s->setInetAddress(createInetAddress(
                                    createString(inet_ntoa(client_address.sin_addr)),
                                    ntohs(client_address.sin_port)));
                    {
                        AutoLock l(mMutex);
                        mSocks->put(clientfd,s);
                    }
                    //mListener->onConnect(s);
                    mListener->onSocketMessage(st(Socket)::Connect,s,nullptr);
                    
                } else {
                    //TODO
                }
            }
            else {
                //byte recv_buf[mRcvBuffSize];
                //memset(recv_buf,0,mRcvBuffSize);
                SSLInfo info = st(SSLManager)::getInstance()->get(sockfd);
                ByteArray buff = createByteArray(mRcvBuffSize);
                int len = info->read(buff);
                if(len == 0 || len == -1) {
                    //this sockfd maybe closed!!!!!
                    //TODO
                    continue;
                }
                
                if(mListener != nullptr) {
                    //SocketResponser r = createSocketResponser(sockfd);
                    Socket s = nullptr;
                    {
                        AutoLock l(mMutex);
                        s = mSocks->get(sockfd);
                    }

                    //mListener->onDataReceived(s,buff);
                    mListener->onSocketMessage(st(Socket)::Message,s,buff);
                }
            }
        }
      
    }
}

//----------------- HttpsServer -----------------
_SSLServer::_SSLServer(int port,SocketListener l,String c,String k):_SSLServer(nullptr,port,l,c,k) {

}

_SSLServer::_SSLServer(String ip,int port,SocketListener l,String c,String k):_SSLServer(ip,
                      port,
                      st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerRcvBuffSize,1024*32),
                      st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerClientNums,1024*32),
                      l,
                      c,k) {

}

_SSLServer::_SSLServer(String ip,int port,int rcvBuffsize,int connectionsNum,SocketListener l,String c,String k) {
    mSSLThread = createSSLThread(ip,port,l,c,k);
    
}

void _SSLServer::setRcvBuffSize(int) {

}

int _SSLServer::getRcvBuffSize() {
    //TODO
    return -1;
}

void _SSLServer::start() {
    mSSLThread->start();
}

void _SSLServer::release() {

}


int _SSLServer::removeClientFd(int fd) {
    //TODO
    return -1;
}

int _SSLServer::addClientFd(int fd) {
    //TODO
    return -1;
}

int _SSLServer::getStatus() {
    //TODO
    return -1;
}

_SSLServer::~_SSLServer() {

}

}

