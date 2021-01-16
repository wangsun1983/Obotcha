#include "WebSocketServer.hpp"

#include <stdio.h>
#include <sys/epoll.h>

#include "Error.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketProtocol.hpp"
#include "HttpClientInfo.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"

namespace obotcha {

//--------------------WebSocketClientManager-----------------
WebSocketClientManager _WebSocketClientManager::mInstance = nullptr;
Mutex _WebSocketClientManager::mMutex = createMutex("WebSocketClientManagerMutex");

_WebSocketClientManager::_WebSocketClientManager() {
    mClients = createHashMap<int, WebSocketClientInfo>();

    mRand = createRandom();
}

uint32_t _WebSocketClientManager::genRandomUint32() {
    return mRand->nextUint32();
}

WebSocketClientManager _WebSocketClientManager::getInstance() {
    if (mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mMutex);

    if (mInstance != nullptr) {
        return mInstance;
    }

    mInstance = AutoClone(new _WebSocketClientManager());
    return mInstance;
}

WebSocketClientInfo _WebSocketClientManager::addClient(int fd, int version) {
    WebSocketClientInfo client = createWebSocketClientInfo();
    client->setClientFd(fd);
    client->setVersion(version);

    switch (version) {
        case 0: {
            client->setParser(createWebSocketHybi00Parser());
            client->setComposer(createWebSocketHybi00Composer(WsServerComposer));
            break;
        }

        case 7: {
            client->setParser(createWebSocketHybi07Parser());
            client->setComposer(createWebSocketHybi07Composer(WsServerComposer));
            break;
        }

        case 8: {
            client->setParser(createWebSocketHybi08Parser());
            client->setComposer(createWebSocketHybi08Composer(WsServerComposer));
            break;
        }

        case 13: {
            client->setParser(createWebSocketHybi13Parser());
            client->setComposer(createWebSocketHybi13Composer(WsServerComposer));
            break;
        }

        default:
            LOG(ERROR)<<"WebSocket Protocol Not Support,Version is "<<version;
            return nullptr;
    }

    AutoLock ll(mMutex);
    mClients->put(fd, client);
    return client;
}

WebSocketClientInfo _WebSocketClientManager::getClient(int fd) {
    AutoLock ll(mMutex);
    return mClients->get(fd);
}

void _WebSocketClientManager::removeClient(WebSocketClientInfo client) {
    AutoLock ll(mMutex);
    mClients->remove(client->getClientFd());
}

//--------------------WebSocketDispatchData-----------------
_DispatchData::_DispatchData(uint64_t clientid,int cmd,int fd, uint32_t events,ByteArray pack) {
    this->fd = fd;
    this->events = events;
    if(pack != nullptr) {
        this->data = createByteArray(pack);
    } else {
        data = nullptr;
    }

    this->cmd = cmd;
    this->clientId = clientid;
}

_DispatchData::_DispatchData(int cmd,int fd, uint32_t events,HttpPacket pack) {
    this->fd = fd;
    this->events = events;
    this->cmd = cmd;
    this->clientId = 0;
    this->packet = pack;
}

//----WebSocketDispatchRunnable----
_WebSocketDispatchRunnable::_WebSocketDispatchRunnable(int index,sp<_WebSocketDispatcherPool> pool) {
    mIndex = index;
    mPoolMutex = createMutex();
    mPool = pool;
    mParser = createHttpRequestParser();
}

void _WebSocketDispatchRunnable::handleHttpData(DispatchData data) {

    int fd = data->fd;
    HttpPacket request = data->packet;
    HttpHeader header = request->getHeader();
    String upgrade = header->getValue(st(HttpHeader)::Upgrade);
    String key = header->getValue(st(HttpHeader)::SecWebSocketKey);
    String version = header->getValue(st(HttpHeader)::SecWebSocketVersion);
    if (upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
        // remove fd from http epoll
        mPool->getHttpServer()->deMonitor(fd);

        while(st(WebSocketClientManager)::getInstance()->getClient(fd)!= nullptr) {
            LOG(INFO)<<"websocket client is not removed,fd is "<<fd;
            usleep(1000*5);
        }
        
        WebSocketClientInfo client = st(WebSocketClientManager)::getInstance()->addClient(fd,
                                                            version->toBasicInt());
        client->setHttpHeader(header);
        WebSocketParser parser = client->getParser();

        if (!parser->validateHandShake(header)) {
            return;
        }

        // Try to check whether extension support deflate.
        WebSocketPermessageDeflate deflate = parser->validateExtensions(header);
        if (deflate != nullptr) {
            client->setDeflater(deflate);
        }
        ArrayList<String> protocols = parser->extractSubprotocols(header);
        if (protocols != nullptr && protocols->size() != 0) {
            LOG(ERROR)<<"Websocket Server Protocol is not null";
        } else {
            //TODO
        }

        mPool->getWebSocketServer()->monitor(fd);
        mPool->getWebSocketServer()->notifyConnect(client);
        WebSocketComposer composer = client->getComposer();
        ByteArray shakeresponse = composer->genShakeHandMessage(client);
        int ret = send(fd,shakeresponse->toValue(),shakeresponse->size(),0);
        if(ret < 0) {
            LOG(ERROR)<<"Websocket Server send response fail,reason:"<<strerror(errno);
        }
    }
}

void _WebSocketDispatchRunnable::handleWsData(DispatchData data) {

    uint32_t events = data->events;
    int fd = data->fd;
    ByteArray pack = data->data;
    bool isRmClient = false;

    WebSocketClientInfo client =
        st(WebSocketClientManager)::getInstance()->getClient(fd);

    WebSocketServer server = mPool->getWebSocketServer();
    
    if(client == nullptr) {
        //receive hungup before.
        return;
    }

    if(client->getClientId() != data->clientId) {
        LOG(ERROR)<<"WebSocket different client error";
        return;
    }

    if((events & EPOLLRDHUP) != 0) {
        if(pack == nullptr || pack->size() == 0) {
            st(WebSocketClientManager)::getInstance()->removeClient(client);
            server->notifyDisconnect(client);
            return;
        }

        isRmClient = true;
    }

    if((events & EPOLLOUT) != 0) {
        client->enableSend();
    }

    WebSocketParser parser = client->getParser();
    WebSocketBuffer defferedBuff = client->getDefferedBuffer();
    if (defferedBuff != nullptr) {
        if(defferedBuff->mBuffer != nullptr) {
            defferedBuff->mBuffer->append(pack);
        } else {
            defferedBuff->mBuffer = pack;
        }
        pack = defferedBuff->mBuffer;
    }

    while (1) {
        int readIndex = 0;
        if (!parser->validateEntirePacket(pack)) {
            // it is not a full packet
            if (defferedBuff == nullptr) {
                defferedBuff = createWebSocketBuffer();
                defferedBuff->mBuffer = pack;
                st(WebSocketClientManager)::getInstance()->getClient(fd)->setDefferedBuffer(defferedBuff);
            }
            break;
        }

        parser->setParseData(pack);
        WebSocketHeader header = parser->parseHeader();

        int opcode = header->getOpCode();
        int framesize = header->getFrameLength();
        int headersize = header->getHeadSize();

        if (opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
            ByteArray msgData = parser->parseContent(true);
            String msg = msgData->toString();
            WebSocketFrame frame = createWebSocketFrame(header,msg);
            server->notifyMessage(client, frame);
        } else if (opcode == st(WebSocketProtocol)::OPCODE_BINARY) {
            if (header->isFinalFrame()) {
                ByteArray msgData = parser->parseContent(true);
                WebSocketFrame frame = createWebSocketFrame(header,msgData);
                server->notifyData(client, msgData);
            } else {
                ByteArray msgData = parser->parseContent(false);
                WebSocketBuffer buff = createWebSocketBuffer();
                buff->mBuffer = msgData;
                client->setContinueBuffer(buff);
            }
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            ByteArray buff = parser->parsePingBuff();
            if (server->notifyPing(client, buff->toString()) == PingResultResponse) {
                ByteArray resp = client->getComposer()->genPongMessage(client,buff->toString());
                send(fd,resp->toValue(),resp->size(),0);
            }
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            ByteArray pong = parser->parsePongBuff();
            String msg = pong->toString();
            server->notifyPong(client, msg);
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            isRmClient = true;
            goto FINISH;
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
            ByteArray msgData = parser->parseContent(false);
            WebSocketBuffer continuebuff = client->getContinueBuffer();
            continuebuff->mBuffer->append(msgData);

            if (header->isFinalFrame()) {
                ByteArray out = parser->validateContinuationContent(
                    client->getContinueBuffer()->mBuffer);
                WebSocketFrame frame = createWebSocketFrame(header,out);
                server->notifyData(client, frame);
                continuebuff->mBuffer = nullptr;
            }
        }

        // check whether there are two ws messages received in one buffer!
        // len -= (framesize + headersize);
        int resetLength = (pack->size() - (framesize + headersize));
        readIndex += (framesize + headersize);
        
        if (resetLength > 0) {
            byte *pdata = pack->toValue();
            pack = createByteArray(&pdata[readIndex], resetLength);
            continue;
        }

        client->setDefferedBuffer(nullptr);
        break;
    }

FINISH:
    if(isRmClient) {
        st(WebSocketClientManager)::getInstance()->removeClient(client);
        server->notifyDisconnect(client);
    }
}

void _WebSocketDispatchRunnable::onInterrupt() {
    mPool = nullptr;
}

void _WebSocketDispatchRunnable::run() {
    DispatchData data = nullptr;
    while(1) {
        {
            data  = mPool->getData(mIndex);
            if(data == nullptr) {
                mPool = nullptr;
                return;
            }
        }
        
        switch(data->cmd) {
            case st(DispatchData)::Http:
            handleHttpData(data);
            break;

            case st(DispatchData)::Ws:
            handleWsData(data);
            break;
        }
    }
}

//----WebSocketDefferedTasks----
_WebSocketDefferedTasks::_WebSocketDefferedTasks() {
    mutex = createMutex();
    tasks = createLinkedList<DispatchData>();
}

//----WebSocketDispatcherPool----
_WebSocketDispatcherPool::_WebSocketDispatcherPool(int threadnum) {
    //fd2TidsMutex = createMutex("WebSocketDispatcherPool");
    mThreadnum = threadnum;
    mDataMutex = createSpinLock();
    mTidFdsMutex = createMutex();
    mDataCondition = createCondition();
    datas = createLinkedList<DispatchData>();
    mExecutor = createThreadPoolExecutor(-1,threadnum);
    mRunnables = createArrayList<WebSocketDispatchRunnable>();
    mDefferedTasks = createArrayList<WebSocketDefferedTasks>();
    isStop = false;

    for(int index = 0;index < threadnum;index++) {
        WebSocketDispatchRunnable r = createWebSocketDispatchRunnable(index,AutoClone(this));
        mRunnables->add(r);
        WebSocketDefferedTasks t = createWebSocketDefferedTasks();
        mDefferedTasks->add(t);
        tid2fds[index] = -1;
    }

    ListIterator<WebSocketDispatchRunnable> iterator = mRunnables->getIterator();
    while(iterator->hasValue()) {
        mExecutor->execute(iterator->getValue());
        iterator->next();
    }
}

void _WebSocketDispatcherPool::addData(DispatchData data) {
    AutoLock l(mTidFdsMutex);
    int tid = getTidByFd(data->fd);
    if(tid != -1) {
        WebSocketDefferedTasks defferedTasks = mDefferedTasks->get(tid);
        defferedTasks->tasks->enQueueLast(data);
        mDataCondition->notifyAll();
        return;
    }
    datas->enQueueLast(data);
    mDataCondition->notifyAll();
}

void _WebSocketDispatcherPool::setHttpServer(HttpServer server) {
    mHttpServer = server;
}

HttpServer _WebSocketDispatcherPool::getHttpServer() {
    return mHttpServer;
}

void _WebSocketDispatcherPool::setWebSocketServer(WebSocketServer w) {
    mWebSocketServer = w;
}

WebSocketServer _WebSocketDispatcherPool::getWebSocketServer() {
    return mWebSocketServer;
}

void _WebSocketDispatcherPool::release() {
    mExecutor->shutdown();
    isStop = true;
    mDataCondition->notifyAll();
    mRunnables->clear();
}

int _WebSocketDispatcherPool::getTidByFd(int fd) {
     //try to find an index
    for(int index = 0;index <mThreadnum;index++) {
        if(tid2fds[index] == fd) {
            return index;
        }
    }

    return -1;
}

DispatchData _WebSocketDispatcherPool::getData(int requireIndex) {
    DispatchData data = nullptr;
    WebSocketDefferedTasks defferedTasks = mDefferedTasks->get(requireIndex);
    while(!isStop) {
        AutoLock l(mTidFdsMutex);
        {
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
            
        }
        mDataCondition->wait(mTidFdsMutex);
        continue;
    }
    return nullptr;
}

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer() {
    mDispatchPool = createWebSocketDispatcherPool();
    mWsEpollObserver = createEPollFileObserver();
    mWsEpollObserver->start();
    mSendTimeout = -1;
    mRcvTimeout = -1;
}

void _WebSocketServer::setSendTimeout(long timeout) {
    mSendTimeout = timeout;
}

long _WebSocketServer::getSendTimeout() {
    return mSendTimeout;
}

void _WebSocketServer::setRcvTimeout(long timeout) {
    mRcvTimeout = timeout;
}

long _WebSocketServer::getRcvTimeout() {
    return mRcvTimeout;
}

int _WebSocketServer::bind(String ip, int port, String path,
                           WebSocketListener listener) {
    if (mHttpServer != nullptr) {
      return -AlreadyExists;
    }

    mWsListener = listener;
    
    if (ip == nullptr) {
        mHttpServer = createHttpServer(port, AutoClone(this));
    } else {
        mHttpServer = createHttpServer(ip, port, AutoClone(this));
    }

    mHttpServer->setSendTimeout(mSendTimeout);
    mHttpServer->setRcvTimeout(mRcvTimeout);
    mHttpServer->start();

    mDispatchPool->setHttpServer(mHttpServer);
    mDispatchPool->setWebSocketServer(AutoClone(this));

    return 0;
}

int _WebSocketServer::bind(int port, String path, WebSocketListener listener) {
    return bind(nullptr, port, path, listener);
}

void _WebSocketServer::monitor(int fd) {
    mWsEpollObserver->addObserver(fd,EPOLLIN|EPOLLRDHUP|EPOLLOUT,AutoClone(this));
}

int _WebSocketServer::start() {
    return 0;
}

int _WebSocketServer::release() {
    mWsEpollObserver->release();
    mDispatchPool->release();
}

//WebSocket Epoll listener
int _WebSocketServer::onEvent(int fd,uint32_t events,ByteArray pack) {
    WebSocketClientInfo client = st(WebSocketClientManager)::getInstance()->getClient(fd);
    
    if(client != nullptr) {
        DispatchData data = createDispatchData(client->getClientId(),st(DispatchData)::Ws,fd,events,pack);
        mDispatchPool->addData(data);
    }
    return st(EPollFileObserver)::OnEventOK;
}

void _WebSocketServer::onMessage(sp<_HttpClientInfo> client,sp<_HttpResponseWriter> w,HttpPacket msg) {
    //int cmd,int fd, uint32_t events,HttpPacket pack
    //_DispatchData::_DispatchData(int cmd,int fd, uint32_t events,HttpPacket pack) {
    DispatchData data = createDispatchData(st(DispatchData)::Http,client->getClientFd(),0,msg);
    mDispatchPool->addData(data);
}

void _WebSocketServer::onConnect(sp<_HttpClientInfo> client) {
    //TODO
    //printf("_WebSocketServer onConnect1,client fd is %d \n",client->getClientFd());
}

void _WebSocketServer::onDisconnect(sp<_HttpClientInfo> client) {
    //TODO
    //printf("_WebSocketServer onConnect2 fd is %d\n",client->getClientFd());
}

int _WebSocketServer::notifyMessage(sp<_WebSocketClientInfo> client,WebSocketFrame frame) {
    return mWsListener->onMessage(client,frame);
}

int _WebSocketServer::notifyData(sp<_WebSocketClientInfo> client,WebSocketFrame frame) {
    return mWsListener->onData(client,frame);
}

int _WebSocketServer::notifyConnect(sp<_WebSocketClientInfo> client) {
    return mWsListener->onConnect(client);
}

int _WebSocketServer::notifyDisconnect(sp<_WebSocketClientInfo> client) {
    return mWsListener->onDisconnect(client); 
}

int _WebSocketServer::notifyPong(sp<_WebSocketClientInfo> client,String msg) {
    return mWsListener->onPong(client,msg); 
}

int _WebSocketServer::notifyPing(sp<_WebSocketClientInfo> client,String msg) {
    return mWsListener->onPing(client,msg); 
}

}  // namespace obotcha
