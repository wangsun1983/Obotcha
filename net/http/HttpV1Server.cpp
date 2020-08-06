#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpClient.hpp"
#include "HttpPacket.hpp"
#include "InetAddress.hpp"
#include "HttpHeader.hpp"
#include "ByteArrayReader.hpp"
#include "Error.hpp"
#include "HttpV1Server.hpp"
#include "InitializeException.hpp"
#include "AutoLock.hpp"
#include "HttpV1ClientInfo.hpp"
#include "HttpClientManager.hpp"
#include "SSLManager.hpp"

namespace obotcha {

//------------------DispatchHttpWorkData------------------
_DispatchHttpWorkData::_DispatchHttpWorkData(int fd,ByteArray pack) {
    this->fd = fd;
    this->pack = pack;
}

//------------------HttpDispatchThread------------------
_HttpDispatchThread::_HttpDispatchThread(HttpDispatchStatusListener l,HttpV1Listener v1listener) {
    datas = createBlockingLinkedList<DispatchHttpWorkData>();
    mWorkedFds = createHashSet<int>();
    mListener = l;
    mV1Listener = v1listener;
}

void _HttpDispatchThread::add(DispatchHttpWorkData data) {
    datas->enQueueLast(data);
}
    
int _HttpDispatchThread::getWorkQueueSize() {
    return datas->size();
}

void _HttpDispatchThread::run() {
    while (1) {
        //mutex
        mListener->lockData();
        if(datas->size() == 0) {
            HashSetIterator<int>iterator = mWorkedFds->getIterator();
            while(iterator->hasValue()) {
                //we should check whether client buff is clear
                int fd = iterator->getValue();
                HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(fd);
                if(info == nullptr || info->isIdle()) {
                    //printf("onIdle,fd is %d \n",fd);
                    mListener->onComplete(fd);
                }
                iterator->next();
            }

            mWorkedFds->clear();
        }
        mListener->unlockData();

        //printf("_HttpDispatchThread run1 \n");
        DispatchHttpWorkData data = datas->deQueueFirst();
        if (data->fd == -1) {
            printf("_HttpDispatchThread run1 fd is null \n");
            continue;
        }

        HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(data->fd);
        if(info == nullptr) {
            continue;
        }
        
        mWorkedFds->add(data->fd);
        
        info->pushHttpData(data->pack);
        //printf("_HttpDispatchThread run2 \n");
        ArrayList<HttpPacket> packets = info->pollHttpPacket();
        if(packets != nullptr && packets->size() != 0) {
            ListIterator<HttpPacket> iterator = packets->getIterator();
            while(iterator->hasValue()) {
                //we should check whether there is a multipart
                HttpV1ResponseWriter writer = createHttpV1ResponseWriter(info);  
                //printf("_HttpDispatchThread run3 \n");         
                mV1Listener->onMessage(info,writer,iterator->getValue());
                iterator->next();
            }
        }
    }
}

void _HttpV1Server::onDataReceived(SocketResponser r,ByteArray pack) {
    //printf("onDataReceived \n");
    AutoLock l(mMutex);
    //parseMessage(r->getFd(),pack);
    Integer threadId = fdmaps->get(r->getFd());
    if(threadId != nullptr) {
        int num = threadId->toValue();
        printf("onDataReceived,add data,threadid is %d \n",num);
        
        mThreads->get(num)->add(createDispatchHttpWorkData(r->getFd(),pack));
        return;
    }

    int hit = 0;
    int min = 0;

    for(int i = 0;i<threadsNum;i++) {
        int size = mThreads->get(i)->getWorkQueueSize();
        if(i == 0) {
          min = size;
        } else if(size < min) {
            hit = i;
            min = size;
        }
    }

    fdmaps->put(r->getFd(),createInteger(hit));
    printf("onDataReceived2,add data,threadid is %d \n",hit);
    mThreads->get(hit)->add(createDispatchHttpWorkData(r->getFd(),pack));
}

void _HttpV1Server::onComplete(int fd) {
    fdmaps->remove(fd);
}

void _HttpV1Server::onDisconnect(SocketResponser r) {
    {
        AutoLock l(mMutex);
        fdmaps->remove(r->getFd());
    }

    HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(r->getFd());
    this->mHttpListener->onDisconnect(info);
    removeClient(r->getFd());
}

void _HttpV1Server::onConnect(SocketResponser r) {
    HttpV1ClientInfo info = createHttpV1ClientInfo();
    info->setClientFd(r->getFd());
    SSLInfo ssl = st(SSLManager)::getInstance()->get(r->getFd());
    if(info != nullptr) {
        info->setSSLInfo(ssl);
    }
    
    st(HttpV1ClientManager)::getInstance()->addClientInfo(r->getFd(),info);
}

void _HttpV1Server::onTimeout() {
    //Unused
}

_HttpV1Server::_HttpV1Server(int port,HttpV1Listener l):_HttpV1Server{nullptr,port,l} {

}

_HttpV1Server::_HttpV1Server(int port,HttpV1Listener l,String certificate,String key):_HttpV1Server{nullptr,port,l,certificate,key}{

}

_HttpV1Server::_HttpV1Server(HttpV1Listener l):_HttpV1Server{nullptr,-1,l} {
    
}

_HttpV1Server::_HttpV1Server(HttpV1Listener l,String certificate,String key):_HttpV1Server{nullptr,-1,l,certificate,key} {
    
}

_HttpV1Server::_HttpV1Server(String ip,int port,HttpV1Listener l):_HttpV1Server{ip,port,l,nullptr,nullptr}{
    
}

_HttpV1Server::_HttpV1Server(String ip,int port,HttpV1Listener l,String certificate,String key) {
    HttpV1Server server;
    server.set_pointer(this);
    mHttpListener = l;

    mMutex = createMutex("httpserver fdmaps");
    fdmaps = createHashMap<int,Integer>();

    threadsNum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
    mThreads = createArrayList<HttpDispatchThread>();
    for(int i = 0;i<threadsNum;i++) {
        HttpDispatchThread thread = createHttpDispatchThread(server,l);
        thread->start();
        mThreads->add(thread);
    }

    mIp = ip;
    mPort = port;

    SocketListener sockListener;
    sockListener.set_pointer(this);
    //printf("_HttpV1Server trace1 \n");
    if(certificate == nullptr) {
        //http server
        if(mIp == nullptr) {
            mTcpServer = createTcpServer(mPort,sockListener);
        } else {
            mTcpServer = createTcpServer(mIp,mPort,sockListener);
        }
        //printf("_HttpV1Server trace2 \n");
        if(mTcpServer->start() != 0) {
            //printf("_HttpV1Server trace3 \n");
            throw InitializeException("tcp server start fail!!");
        }
    } else {
        //https server
        mSSLServer = createSSLServer(ip,port,sockListener,certificate,key);
        mSSLServer->start();
    }
    
    mBuffPoolMutex = createMutex("HttpV1Server mutex");
    mBuffPool = createHashMap<int,ByteArray>();
}

void _HttpV1Server::parseMessage(int fd,ByteArray pack) {
    
}

void _HttpV1Server::addClient(int fd) {
    HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(fd);
    mHttpListener->onConnect(info);
}

void _HttpV1Server::removeClient(int fd) {
   HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->removeClientInfo(fd);
   mHttpListener->onDisconnect(info);
}

void _HttpV1Server::exit() {
    if(mTcpServer != nullptr) {
        mTcpServer->release();
    }

    if(mSSLServer != nullptr) {
        mSSLServer->release();
    }
    
    st(HttpV1ClientManager)::getInstance()->clear();
}

void _HttpV1Server::lockData() {
    mMutex->lock();
}

void _HttpV1Server::unlockData() {
    mMutex->unlock();
}

}

