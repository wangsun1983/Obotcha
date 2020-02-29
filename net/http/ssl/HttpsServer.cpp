#include "HttpsServer.hpp"
#include "Enviroment.hpp"
#include "NetUtils.hpp"
#include "InitializeException.hpp"

namespace obotcha {

//----------------- HttpsThread -----------------
_HttpsThread::_HttpsThread(String ip,int port,SocketListener l,String c,String k) {
    String mIp = ip;

    int mPort = port;

    mCertificate = c;

    mKey = k;
    
    mClients = createHashMap<int,SSL *>();

    const int EPOLL_SIZE = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerEpollSize,1024);
    if(l == nullptr) {
        throw InitializeException("SocketListener is null");
    }

    mSockAddr.sin_family = PF_INET;
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
        
        mSocket = socket(AF_INET, SOCK_STREAM, 0);
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
        if(st(NetUtils)::addEpollFd(mEpollfd,mSocket,true) < 0) {
            break;
        }

        if(st(NetUtils)::addEpollFd(mEpollfd,mPipe->getReadPipe(),true) < 0) {
            break;
        }
       
        return;
    }
}

void _HttpsThread::run() {
    const int EPOLL_SIZE = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerEpollSize,1024);
    struct epoll_event events[EPOLL_SIZE];
    printf("https thread1 start \n");
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
                //printf("hangup sockfd!!!!,sockefd is %d \n",sockfd);
                epoll_ctl(mEpollfd, EPOLL_CTL_DEL, sockfd, NULL);
                st(NetUtils)::delEpollFd(mEpollfd,sockfd);
                mListener->onDisconnect(sockfd);
                close(sockfd);
                continue;
            }
            
            if(sockfd == mSocket) {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                int clientfd = accept( mSocket, ( struct sockaddr* )&client_address, &client_addrLength );
                printf("https thread1 trace1 \n");
                SSL *ssl = initSSL();
                if (!SSL_set_fd(ssl, clientfd)) {
                    continue;
                }

                mClients->put(clientfd,ssl);
 
                st(NetUtils)::addEpollFd(mEpollfd, clientfd, true);
                printf("https thread1 trace2,connect clientfd is %d.ssl is %p \n",clientfd,ssl);
                SSL_accept(ssl);
                printf("https thread1 trace3 \n");
                mListener->onConnect(clientfd,
                                    createString(inet_ntoa(client_address.sin_addr)),
                                    ntohs(client_address.sin_port));
            }
            else {
                byte recv_buf[mBuffSize];
                memset(recv_buf,0,mBuffSize);

                SSL *ssl = mClients->get(sockfd);
                printf("https thread1 trace4,sockfd is %d,ssl is %p \n",sockfd,ssl);
                int len = SSL_read(ssl, recv_buf, mBuffSize);
                if(len == 0 || len == -1) {
                    //this sockfd maybe closed!!!!!
                    //printf("tcpserver error len is %d,sockfd is %d \n",len,sockfd);
                    printf("https thread1 trace4_1 len is %d,ssl is %p \n",len,ssl);
                    continue;
                }
                ByteArray pack = createByteArray(&recv_buf[0],len);
                printf("https thread1 trace5 \n");
                if(mListener != nullptr) {
                    printf("https thread1 trace6 \n");
                    mListener->onAccept(sockfd,nullptr,-1,pack);
                }
            }
        }
      
    }
}

SSL * _HttpsThread::initSSL() {
    
    if(mCertificate == nullptr) {
        mCertificate = st(Enviroment)::getInstance()->get(st(Enviroment)::gHttpSslCertificatePath);
    }
    
    if(mKey == nullptr) {
        mKey = st(Enviroment)::getInstance()->get(st(Enviroment)::gHttpSslKeyPath);
    }

    /* int ssl  */
    SSL_library_init();
    /* load SSL algorithms */
    OpenSSL_add_all_algorithms();
    /* load SSL error strings */
    SSL_load_error_strings();

    /*can use SSLv2_server_method() or SSLv3_server_method()*/
    SSL_CTX *mCtx = SSL_CTX_new(SSLv23_server_method());
    if (mCtx == NULL) {
        throw InitializeException("SSL Create error");
    }
    /* load user certificate,this certificati is used to send to client,certificate contains public key */
    if (SSL_CTX_use_certificate_file(mCtx, mCertificate->toChars(), SSL_FILETYPE_PEM) <= 0) {
	    throw InitializeException("SSL certificate use error");
    }
    /* load private key */
    if (SSL_CTX_use_PrivateKey_file(mCtx, mKey->toChars(), SSL_FILETYPE_PEM) <= 0) {
        throw InitializeException("SSL private key use error");
    }
    /* check whether private is ok */
    if (!SSL_CTX_check_private_key(mCtx)) {
        throw InitializeException("SSL private key check error");
    }

    return SSL_new(mCtx);
}

//----------------- HttpsServer -----------------
_HttpsServer::_HttpsServer(int port,SocketListener l,String c,String k):_HttpsServer(nullptr,port,l,c,k) {

}

_HttpsServer::_HttpsServer(String ip,int port,SocketListener l,String c,String k):_HttpsServer(ip,
                      port,
                      st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerRcvBuffSize,1024*32),
                      st(Enviroment)::getInstance()->getInt(st(Enviroment)::gTcpServerClientNums,1024*32),
                      l,
                      c,k) {

}

_HttpsServer::_HttpsServer(String ip,int port,int rcvBuffsize,int connectionsNum,SocketListener l,String c,String k) {
    mHttpThread = createHttpsThread(ip,port,l,c,k);
    
}

void _HttpsServer::setRcvBuffSize(int) {

}

int _HttpsServer::getRcvBuffSize() {

}

int _HttpsServer::start() {
    mHttpThread->start();
}

void _HttpsServer::release() {

}


int _HttpsServer::removeClientFd(int fd) {

}

int _HttpsServer::addClientFd(int fd) {

}

int _HttpsServer::getStatus() {

}

_HttpsServer::~_HttpsServer() {

}

}

