#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpPacket.hpp"
#include "InetAddress.hpp"
#include "HttpHeader.hpp"
#include "Error.hpp"
#include "HttpServer.hpp"
#include "AutoLock.hpp"
#include "HttpClientInfo.hpp"
#include "HttpResponseWriter.hpp"
#include "HttpClientManager.hpp"
#include "SSLManager.hpp"
#include "InterruptedException.hpp"
#include "HttpInternalException.hpp"
#include "SocketBuilder.hpp"
#include "SocketOption.hpp"

namespace obotcha {

//------------------HttpTaskData------------------
_HttpTaskData::_HttpTaskData(int fd,ByteArray pack,uint64_t id) {
    this->fd = fd;
    this->pack = pack;
    this->clientid = id;
}

_HttpDispatcherPool::_HttpDispatcherPool(sp<_HttpServer> server,int threadSize) {
    mExecutors = createThreadPoolExecutor(-1,threadSize);
    datas = createLinkedList<HttpTaskData>();
    mTaskGroup = createArrayList<LinkedList<HttpTaskData>>();
    mDataMutex = createMutex();
    mDataCondition = createCondition();
    isStop = false;
    
    for(int index = 0;index < threadSize;index++) {
        mTaskGroup->add(createLinkedList<HttpTaskData>());
        GroupIdTofds[index] = -1;
        mExecutors->execute([](HttpServer server,HttpDispatcherPool pool,int num) {
            while(1) {
                printf("_HttpDispatcherPool trace1 \n");
                HttpTaskData data = pool->getData(num);
                
                if(data == nullptr) {
                    return;
                }
                printf("_HttpDispatcherPool trace2 \n");
                HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(data->fd);
                if(info == nullptr || data->clientid != info->getClientId()) {
                    continue;
                }
                printf("_HttpDispatcherPool trace3 \n");
                try {
                    info->pushHttpData(data->pack);
                } catch(HttpInternalException &e) {
                    st(HttpClientManager)::getInstance()->removeClientInfo(info->getClientFd());
                    info->close();
                    continue;
                }
                printf("_HttpDispatcherPool trace4 \n");
                ArrayList<HttpPacket> packets = info->pollHttpPacket();
                if(packets != nullptr && packets->size() != 0) {
                    HttpResponseWriter writer = createHttpResponseWriter(info);
                    ListIterator<HttpPacket> iterator = packets->getIterator();
                    while(iterator->hasValue()) {
                        server->mHttpListener->onMessage(info,writer,iterator->getValue());
                        iterator->next();
                    }
                }
            }
        },server,AutoClone(this),index);
    }
}

void _HttpDispatcherPool::addData(HttpTaskData data) {
    AutoLock l(mDataMutex);
    int index = getGroupIdByFd(data->fd);
    
    if(index != -1) {
        mTaskGroup->get(index)->enQueueLast(data);
        mDataCondition->notifyAll();
        return;
    }
    
    datas->enQueueLast(data);
    mDataCondition->notifyAll();
}

int _HttpDispatcherPool::getGroupIdByFd(int fd) {
    //try to find an index
    AutoLock l(mDataMutex);
    for(int index = 0;index < mExecutors->getThreadsNum();index++) {
        if(GroupIdTofds[index] == fd) {
            return index;
        }
    }
    return -1;
}

void _HttpDispatcherPool::release() {
    mExecutors->shutdown();
    this->isStop = true;

    AutoLock l(mDataMutex);
    mDataCondition->notifyAll();
}

HttpTaskData _HttpDispatcherPool::getData(int requireIndex) {
    HttpTaskData data = nullptr;
    while(!isStop) {
        AutoLock l(mDataMutex);
        data = mTaskGroup->get(requireIndex)->deQueueFirst();

        if(data == nullptr) {
            GroupIdTofds[requireIndex] = -1;
        } else {
            return data;
        }

        data = datas->deQueueFirst();
        if(data != nullptr) {
            GroupIdTofds[requireIndex] = data->fd;
            return data;
        }
        try {
            mDataCondition->wait(mDataMutex);
        } catch(InterruptedException &e) {
            return nullptr;
        }

        continue;
    }

    return nullptr;
}

void _HttpServer::onDataReceived(Socket r,ByteArray pack) {
    printf("_HttpServer::onDataReceived \n");
    HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(r->getFd());
    HttpTaskData data = createHttpTaskData(r->getFd(),pack,info->getClientId());
    mPool->addData(data);
}

void _HttpServer::onDisconnect(Socket r) {
    printf("_HttpServer::onDisconnect \n");
    HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(r->getFd());
    mHttpListener->onDisconnect(info);
    mSockMonitor->remove(r);
}

void _HttpServer::onConnect(Socket r) {
    printf("_HttpServer::onConnect \n");
    HttpClientInfo info = createHttpClientInfo(createSocketBuilder()
                                                ->setFd(r->getFd())
                                                ->newSocket());

    SSLInfo ssl = st(SSLManager)::getInstance()->get(r->getFd());
    if(info != nullptr) {
        info->setSSLInfo(ssl);
    }
    st(HttpClientManager)::getInstance()->addClientInfo(r->getFd(),info);
    mSockMonitor->bind(r->getFd(),AutoClone(this));
    mHttpListener->onConnect(info);
}

void _HttpServer::onTimeout() {
    //Unused
}

_HttpServer::_HttpServer(int port,HttpListener l):_HttpServer(nullptr,port,l) {

}

_HttpServer::_HttpServer(int port,HttpListener l,String certificate,String key):_HttpServer(nullptr,port,l,certificate,key){

}

_HttpServer::_HttpServer(HttpListener l):_HttpServer(nullptr,-1,l) {
    
}

_HttpServer::_HttpServer(HttpListener l,String certificate,String key):_HttpServer(nullptr,-1,l,certificate,key) {
    
}

_HttpServer::_HttpServer(String ip,int port,HttpListener l):_HttpServer(ip,port,l,nullptr,nullptr){
    
}

_HttpServer::_HttpServer(String ip,int port,HttpListener l,String certificate,String key) {
    mHttpListener = l;

    int threadsNum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
    mPool = createHttpDispatcherPool(AutoClone(this),threadsNum);

    mIp = ip;
    mPort = port;
    mServerSock = nullptr;
    mSockMonitor = nullptr;
    
    mSSLServer = nullptr;

    mCertificate = certificate;
    mKey = key;
    mSendTimeout = -1;
    mRcvTimeout = -1;
}

void _HttpServer::start() {
    if(mCertificate == nullptr) {
        InetAddress address = createInetAddress();
        if(mIp != nullptr) {
            address->setAddress(mIp);
        }

        address->setPort(mPort);

        SocketOption option = createSocketOption();
        if(mSendTimeout != -1) {
            option->setSendTimeout(mSendTimeout);
        }

        if(mRcvTimeout != -1) {
            option->setRecvTimeout(mRcvTimeout);
        }
        printf("http server start \n");
        mServerSock = createSocketBuilder()
                        ->setAddress(address)
                        ->newServerSocket();
        mServerSock->bind();
        printf("http server trace1 \n");
        mSockMonitor = createSocketMonitor();
        printf("http server trace2 \n");
        mSockMonitor->bind(mServerSock,AutoClone(this));
        printf("http server trace3 \n");
    } else {
        //https server
        mSSLServer = createSSLServer(mIp,mPort,AutoClone(this),mCertificate,mKey);
    }
}

void _HttpServer::setSendTimeout(long timeout) {
    mSendTimeout = timeout;
}

long _HttpServer::getSendTimeout() {
    return mSendTimeout;
}

void _HttpServer::setRcvTimeout(long timeout) {
    mRcvTimeout = timeout;
}

long _HttpServer::getRcvTimeout() {
    return mRcvTimeout;
}

//interface for websocket
void _HttpServer::deMonitor(int fd) {
    //mTcpServer->deMonitor(fd);
    printf("demonitor \n");
    //TODO
    //mSockMonitor->remove(fd);
    //st(HttpClientManager)::getInstance()->removeClientInfo(fd);
}

void _HttpServer::exit() {
    printf("http server exit \n");
    if(mServerSock != nullptr) {
        mServerSock->close();
    }

    if(mSSLServer != nullptr) {
        mSSLServer->release();
    }

    if(mPool != nullptr) {
        mPool->release();
    }
    
    st(HttpClientManager)::getInstance()->clear();
}

}

