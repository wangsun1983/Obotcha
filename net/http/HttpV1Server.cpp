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

_HttpDefferedTasks::_HttpDefferedTasks() {
    isDoDefferedTask = false;
    mutex = createMutex();
    tasks = createLinkedList<DispatchHttpWorkData>();
}

//------------------DispatchHttpWorkData------------------
_DispatchHttpWorkData::_DispatchHttpWorkData(int fd,ByteArray pack,int id) {
    this->fd = fd;
    this->pack = pack;
    this->clientid = id;
}

_HttpDispatcherPool::_HttpDispatcherPool(int threadSize) {
    fd2TidsMutex = createMutex("HttpDispatcherPool");
    mThreadnum = threadSize;
    mRunnables = createArrayList<HttpDispatchRunnable>();
    mExecutors = createThreadPoolExecutor(-1,threadSize);
    datas = createLinkedList<DispatchHttpWorkData>();
    mDefferedTasks = createArrayList<HttpDefferedTasks>();
    mDataMutex = createMutex();
    mDataCondition = createCondition();
    
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
    datas->enQueueLast(data);
    mDataCondition->notifyAll();
}

void _HttpDispatcherPool::clearFds(int index) {
    /*
    for(auto it = fd2Tids.begin();it != fd2Tids.end();) {
        if(it->second == index) {
            it = fd2Tids.erase(it);
            continue;
        }
        it++;
    }
     */
}

void _HttpDispatcherPool::release() {
    mExecutors->shutdown();
    ListIterator<HttpDispatchRunnable> iterator = mRunnables->getIterator();
    while(iterator->hasValue()) {
        HttpDispatchRunnable r = iterator->getValue();
        r->release();
    }
}

DispatchHttpWorkData _HttpDispatcherPool::getData(int requireIndex) {
    while(1) {
        DispatchHttpWorkData data = nullptr;
        HttpDefferedTasks defferedTasks = mDefferedTasks->get(requireIndex);
        {
            //search deffered tasks
            {
                AutoLock ll(defferedTasks->mutex);
                data = defferedTasks->tasks->deQueueFirst();
            }
            if(data == nullptr) {
                if(defferedTasks->isDoDefferedTask) {
                    AutoLock l(fd2TidsMutex);
                    //clearFds(requireIndex);
                    tid2fds[requireIndex] = -1;
                    defferedTasks->isDoDefferedTask = false;
                }
            } else {
                defferedTasks->isDoDefferedTask = true;
                return data;
            }
        }
        
        {
            AutoLock l(mDataMutex);
            data = datas->deQueueFirst();
        }
        
        if(data != nullptr) {
            int runnableIndex = -1;
            {
                AutoLock l(fd2TidsMutex);
                //auto iterator = fd2Tids.find(data->fd);
                //if(iterator != fd2Tids.end()) {
                //    runnableIndex = iterator->second;
                //}
                for(int index = 0;index <mThreadnum;index++) {
                    if(tid2fds[index] == data->fd) {
                        runnableIndex = index;
                        break;
                    }
                }
            }

            if(runnableIndex != -1 && requireIndex != runnableIndex) {
                HttpDefferedTasks otherDefferedTasks = mDefferedTasks->get(runnableIndex);
                AutoLock ll(otherDefferedTasks->mutex);
                otherDefferedTasks->tasks->enQueueLast(data);
                {
                    AutoLock l(fd2TidsMutex);
                    //fd2Tids[data->fd] = runnableIndex;
                    tid2fds[runnableIndex] = data->fd;
                }
                mDataCondition->notifyAll();
                continue;
            }
        } else {
            AutoLock l(defferedTasks->mutex);
            if(defferedTasks->tasks->size() != 0) {
                continue;
            }
            mDataCondition->wait(defferedTasks->mutex);
            continue;
        }

        AutoLock l(fd2TidsMutex);
        //fd2Tids[data->fd] = requireIndex;
        tid2fds[requireIndex] = data->fd;
        
        return data;
    }
}

_HttpDispatchRunnable::_HttpDispatchRunnable(int index,HttpDispatcherPool pool) {
    mIndex = index;
    mPoolMutex = createMutex("HttpPoolMutex");
    mPool = pool;
}

void _HttpDispatchRunnable::release() {
    AutoLock l(mPoolMutex);
    mPool = nullptr;
}

void _HttpDispatchRunnable::run() {
    bool isDoDefferedTask = false;
    while(1) {
        DispatchHttpWorkData data = mPool->getData(mIndex);
        HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(data->fd);
        if(info == nullptr) {
            continue;
        }

        info->pushHttpData(data->pack);
        ArrayList<HttpPacket> packets = info->pollHttpPacket();
        HttpV1ResponseWriter writer = createHttpV1ResponseWriter(info);
        //printf("data->clientid is %llx,info->clientfd is %llx \n",data->clientid,info->getClientFd());
        if(data->clientid != info->getClientId()) {
            writer->disableResponse();
        }
        if(packets != nullptr && packets->size() != 0) {
            ListIterator<HttpPacket> iterator = packets->getIterator();
            while(iterator->hasValue()) {
                //we should check whether there is a multipart
                info->getHttpV1Listener()->onMessage(info,writer,iterator->getValue());
                iterator->next();
            }
        }
    }
}

void _HttpV1Server::onDataReceived(SocketResponser r,ByteArray pack) {
    HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(r->getFd());
    DispatchHttpWorkData data = createDispatchHttpWorkData(r->getFd(),pack,info->getClientId());
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

void _HttpV1Server::deMonitor(int fd) {
    mTcpServer->deMonitor(fd);
    st(HttpV1ClientManager)::getInstance()->removeClientInfo(fd);
}

void _HttpV1Server::exit() {
    if(mTcpServer != nullptr) {
        mTcpServer->release();
    }

    if(mSSLServer != nullptr) {
        mSSLServer->release();
    }

    if(mPool != nullptr) {
        mPool->release();
    }
    
    st(HttpV1ClientManager)::getInstance()->clear();
}

}

