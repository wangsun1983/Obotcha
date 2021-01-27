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
#include "HttpServer.hpp"
#include "InitializeException.hpp"
#include "AutoLock.hpp"
#include "HttpClientInfo.hpp"
#include "HttpResponseWriter.hpp"
#include "HttpClientManager.hpp"
#include "SSLManager.hpp"

namespace obotcha {

_HttpDefferedTasks::_HttpDefferedTasks() {
    isDoDefferedTask = false;
    mutex = createMutex();
    tasks = createLinkedList<DispatchHttpWorkData>();
}

//------------------DispatchHttpWorkData------------------
_DispatchHttpWorkData::_DispatchHttpWorkData(int fd,ByteArray pack,uint64_t id) {
    this->fd = fd;
    this->pack = pack;
    this->clientid = id;
}

_HttpDispatcherPool::_HttpDispatcherPool(int threadSize) {
    //fd2TidsMutex = createMutex("HttpDispatcherPool");
    mThreadnum = threadSize;
    mRunnables = createArrayList<HttpDispatchRunnable>();
    mExecutors = createThreadPoolExecutor(-1,threadSize);
    datas = createLinkedList<DispatchHttpWorkData>();
    mDefferedTasks = createArrayList<HttpDefferedTasks>();
    mDataMutex = createMutex();
    mDataCondition = createCondition();
    isStop = false;
    
    for(int index = 0;index < threadSize;index++) {
        HttpDispatchRunnable r = createHttpDispatchRunnable(index,AutoClone(this));
        mRunnables->add(r);

        HttpDefferedTasks t = createHttpDefferedTasks();
        mDefferedTasks->add(t);

        tid2fds[index] = -1;
    }

    ListIterator<HttpDispatchRunnable> iterator = mRunnables->getIterator();
    while(iterator->hasValue()) {
        mExecutors->execute(iterator->getValue());
        iterator->next();
    } 
}

void _HttpDispatcherPool::addData(DispatchHttpWorkData data) {
    AutoLock l(mDataMutex);
    int tid = getTidByFd(data->fd);
    
    if(tid != -1) {
        HttpDefferedTasks defferedTasks = mDefferedTasks->get(tid);
        defferedTasks->tasks->enQueueLast(data);
        mDataCondition->notifyAll();
        return;
    }
    datas->enQueueLast(data);
    mDataCondition->notifyAll();
}

int _HttpDispatcherPool::getTidByFd(int fd) {
     //try to find an index
    for(int index = 0;index <mThreadnum;index++) {
        if(tid2fds[index] == fd) {
            return index;
        }
    }

    return -1;
}

void _HttpDispatcherPool::release() {
    mExecutors->shutdown();
    this->isStop = true;
    mDataCondition->notifyAll();
    mRunnables->clear();
}

DispatchHttpWorkData _HttpDispatcherPool::getData(int requireIndex) {
    DispatchHttpWorkData data = nullptr;
    HttpDefferedTasks defferedTasks = mDefferedTasks->get(requireIndex);
    while(!isStop) {
        AutoLock l(mDataMutex);
        //search deffered tasks
        data = defferedTasks->tasks->deQueueFirst();

        if(data == nullptr) {
            tid2fds[requireIndex] = -1;
        } else {
            return data;
        }

        data = datas->deQueueFirst();
        if(data != nullptr) {
            tid2fds[requireIndex] = data->fd;
            return data;
        }

        mDataCondition->wait(mDataMutex);
        continue;
    }

    return nullptr;
}

_HttpDispatchRunnable::_HttpDispatchRunnable(int index,HttpDispatcherPool pool) {
    mIndex = index;
    mPool = pool;
}

void _HttpDispatchRunnable::onInterrupt() {
    mPool = nullptr;
}

void _HttpDispatchRunnable::run() {
    bool isDoDefferedTask = false;
    while(1) {
        DispatchHttpWorkData data = mPool->getData(mIndex);
        
        if(data == nullptr) {
            mPool = nullptr;
            return;
        }
        HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(data->fd);
        if(info == nullptr) {
            continue;
        }

        info->pushHttpData(data->pack);
        //printf("HttpDispatchRunnable run trace1,data->pack is %s \n",data->pack->toString()->toChars());
        ArrayList<HttpPacket> packets = info->pollHttpPacket();
        printf("HttpDispatchRunnable run packets size is %d \n",packets->size());
        HttpResponseWriter writer = createHttpResponseWriter(info);
        if(data->clientid != info->getClientId()) {
            writer->disableResponse();
        }

        if(packets != nullptr && packets->size() != 0) {
            ListIterator<HttpPacket> iterator = packets->getIterator();
            while(iterator->hasValue()) {
                //we should check whether there is a multipart
                HttpPacket packet = iterator->getValue();
                packet->dump();
                info->getHttpListener()->onMessage(info,writer,iterator->getValue());
                iterator->next();
            }
        }
    }
}

void _HttpServer::onDataReceived(SocketResponser r,ByteArray pack) {
    HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(r->getFd());
    DispatchHttpWorkData data = createDispatchHttpWorkData(r->getFd(),pack,info->getClientId());
    mPool->addData(data);
}

void _HttpServer::onDisconnect(SocketResponser r) {
    HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(r->getFd());
    mHttpListener->onDisconnect(info);
}

void _HttpServer::onConnect(SocketResponser r) {
    HttpClientInfo info = createHttpClientInfo(mTcpServer->getSocket(r->getFd()));
    info->setHttpListener(mHttpListener);
    //info->setClientFd(r->getFd());
    SSLInfo ssl = st(SSLManager)::getInstance()->get(r->getFd());
    if(info != nullptr) {
        info->setSSLInfo(ssl);
    }
    st(HttpClientManager)::getInstance()->addClientInfo(r->getFd(),info);
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
    mPool = createHttpDispatcherPool(threadsNum);

    mIp = ip;
    mPort = port;
    mTcpServer = nullptr;
    mSSLServer = nullptr;

    if(certificate == nullptr) {
        //http server
        if(mIp == nullptr) {
            mTcpServer = createTcpServer(mPort,AutoClone(this));
        } else {
            mTcpServer = createTcpServer(mIp,mPort,AutoClone(this));
        }
    } else {
        //https server
        mSSLServer = createSSLServer(ip,port,AutoClone(this),certificate,key);
    }
}

void _HttpServer::start() {
    if(mTcpServer != nullptr) {
        mTcpServer->setRcvTimeout(mRcvTimeout);
        mTcpServer->setSendTimeout(mSendTimeout);

        if(mTcpServer->start() != 0) {
            Trigger(InitializeException,"tcp server start fail!!");
        }
    } else if(mSSLServer != nullptr) {
        mSSLServer->start();
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

void _HttpServer::deMonitor(int fd) {
    mTcpServer->deMonitor(fd);
    st(HttpClientManager)::getInstance()->removeClientInfo(fd);
}

void _HttpServer::exit() {
    if(mTcpServer != nullptr) {
        mTcpServer->release();
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

