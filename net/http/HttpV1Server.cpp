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
#include "HttpV1ResponseWriter.hpp"
#include "HttpClientManager.hpp"
#include "SSLManager.hpp"

namespace obotcha {

//------------------DispatchHttpWorkData------------------
_DispatchHttpWorkData::_DispatchHttpWorkData(int fd,ByteArray pack) {
    this->fd = fd;
    this->pack = pack;
}

_HttpDispatcherPool::_HttpDispatcherPool(int threadSize) {
    fd2TidsMutex = createMutex("HttpDispatcherPool");
    mRunnables = createArrayList<HttpDispatchRunnable>();
    mExecutors = createThreadPoolExecutor(-1,threadSize);
    datas = createBlockingLinkedList<DispatchHttpWorkData>();
    for(int index = 0;index < threadSize;index++) {
        HttpDispatchRunnable r = createHttpDispatchRunnable(index,AutoClone(this));
        mExecutors->execute(r);
        mRunnables->add(r);
    }
}

void _HttpDispatcherPool::addData(DispatchHttpWorkData data) {
    datas->enQueueLast(data);
}

void _HttpDispatcherPool::clearFds(int index) {
    for(auto it = fd2Tids.begin();it != fd2Tids.end();) {
        if(it->second == index) {
            it = fd2Tids.erase(it);
            continue;
        }
        it++;
    }
}

void _HttpDispatcherPool::release() {
    //TODO
}

DispatchHttpWorkData _HttpDispatcherPool::getData(int runnableIndex) {
    while(1) {
        DispatchHttpWorkData data = datas->deQueueFirst();
        int runnableIndex = -1;
        {
            AutoLock l(fd2TidsMutex);
            auto iterator = fd2Tids.find(data->fd);
            if(iterator != fd2Tids.end()) {
                runnableIndex = iterator->second;
            }
        }

        if(runnableIndex != -1) {
            HttpDispatchRunnable runnable = mRunnables->get(runnableIndex);
            runnable->addDefferedTask(data);
            continue;
        }

        {
            AutoLock l(fd2TidsMutex);
            fd2Tids[data->fd] = runnableIndex;
        }

        return data;
    }
}

_HttpDispatchRunnable::_HttpDispatchRunnable(int index,HttpDispatcherPool pool) {
    mIndex = index;
    mDefferedTaskMutex = createMutex("HttpDispatchRunnable");
    mDefferedTasks = createLinkedList<DispatchHttpWorkData>();
    mPool = pool;
}

void _HttpDispatchRunnable::run() {
    bool isDoDefferedTask = false;
    while(1) {
        DispatchHttpWorkData data = nullptr;
        {
            AutoLock l(mDefferedTaskMutex);
            data = mDefferedTasks->deQueueFirst();
            if(data != nullptr) {
                isDoDefferedTask = true;
                goto doAction;
            }
        }

        if(isDoDefferedTask) {
            //clear fidmaps
            mPool->clearFds(mIndex);
        }

        isDoDefferedTask = false;
        data = mPool->getData(mIndex);

doAction:
        HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(data->fd);
        if(info == nullptr) {
            continue;
        }

        info->pushHttpData(data->pack);
        ArrayList<HttpPacket> packets = info->pollHttpPacket();
        if(packets != nullptr && packets->size() != 0) {
            HttpV1ResponseWriter writer = createHttpV1ResponseWriter(info); 
            ListIterator<HttpPacket> iterator = packets->getIterator();
            while(iterator->hasValue()) {
                //we should check whether there is a multipart
                info->getHttpV1Listener()->onMessage(info,writer,iterator->getValue());
                iterator->next();
            }
        }
    }
}

void _HttpDispatchRunnable::addDefferedTask(DispatchHttpWorkData data) {
    AutoLock l(mDefferedTaskMutex);
    mDefferedTasks->enQueueLast(data);
}

void _HttpV1Server::onDataReceived(SocketResponser r,ByteArray pack) {
    DispatchHttpWorkData data = createDispatchHttpWorkData(r->getFd(),pack);
    mPool->addData(data);
}

void _HttpV1Server::onDisconnect(SocketResponser r) {
    HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(r->getFd());
    mHttpListener->onDisconnect(info);
}

void _HttpV1Server::onConnect(SocketResponser r) {
    HttpV1ClientInfo info = createHttpV1ClientInfo();
    info->setHttpV1Listener(mHttpListener);
    info->setClientFd(r->getFd());
    SSLInfo ssl = st(SSLManager)::getInstance()->get(r->getFd());
    if(info != nullptr) {
        info->setSSLInfo(ssl);
    }
    st(HttpV1ClientManager)::getInstance()->addClientInfo(r->getFd(),info);
    mHttpListener->onConnect(info);
}

void _HttpV1Server::onTimeout() {
    //Unused
}

_HttpV1Server::_HttpV1Server(int port,HttpV1Listener l):_HttpV1Server(nullptr,port,l) {

}

_HttpV1Server::_HttpV1Server(int port,HttpV1Listener l,String certificate,String key):_HttpV1Server(nullptr,port,l,certificate,key){

}

_HttpV1Server::_HttpV1Server(HttpV1Listener l):_HttpV1Server(nullptr,-1,l) {
    
}

_HttpV1Server::_HttpV1Server(HttpV1Listener l,String certificate,String key):_HttpV1Server(nullptr,-1,l,certificate,key) {
    
}

_HttpV1Server::_HttpV1Server(String ip,int port,HttpV1Listener l):_HttpV1Server(ip,port,l,nullptr,nullptr){
    
}

_HttpV1Server::_HttpV1Server(String ip,int port,HttpV1Listener l,String certificate,String key) {
    mHttpListener = l;

    int threadsNum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
    mPool = createHttpDispatcherPool(threadsNum);

    mIp = ip;
    mPort = port;

    if(certificate == nullptr) {
        //http server
        if(mIp == nullptr) {
            mTcpServer = createTcpServer(mPort,AutoClone(this));
        } else {
            mTcpServer = createTcpServer(mIp,mPort,AutoClone(this));
        }

        if(mTcpServer->start() != 0) {
            Trigger(InitializeException,"tcp server start fail!!");
        }
    } else {
        //https server
        mSSLServer = createSSLServer(ip,port,AutoClone(this),certificate,key);
        mSSLServer->start();
    }
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

}

