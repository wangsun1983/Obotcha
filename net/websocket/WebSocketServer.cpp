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
#include "HttpV1ClientInfo.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"

namespace obotcha {

const int _DispatchData::Http = 0;
const int _DispatchData::Ws = 1;

//--------------------WebSocketClientManager-----------------
WebSocketClientManager _WebSocketClientManager::mInstance = nullptr;
Mutex _WebSocketClientManager::mMutex = createMutex("WebSocketClientManagerMutex");

_WebSocketClientManager::_WebSocketClientManager() {
    mClients = createHashMap<int, WebSocketClientInfo>();
}

WebSocketClientManager _WebSocketClientManager::getInstance() {
    if (mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mMutex);

    if (mInstance != nullptr) {
        return mInstance;
    }

    _WebSocketClientManager *v = new _WebSocketClientManager();
    mInstance.set_pointer(v);
    return mInstance;
}

bool _WebSocketClientManager::addClient(int fd, int version) {
    WebSocketClientInfo data = createWebSocketClientInfo();
    data->setClientFd(fd);
    data->setVersion(version);

    switch (version) {
        case 0: {
            data->setParser(createWebSocketHybi00Parser());
            data->setComposer(createWebSocketHybi00Composer(WsServerComposer));
            break;
        }

        case 7: {
            data->setParser(createWebSocketHybi07Parser());
            data->setComposer(createWebSocketHybi07Composer(WsServerComposer));
            break;
        }

        case 8: {
            data->setParser(createWebSocketHybi08Parser());
            data->setComposer(createWebSocketHybi08Composer(WsServerComposer));
            break;
        }

        case 13: {
            data->setParser(createWebSocketHybi13Parser());
            data->setComposer(createWebSocketHybi13Composer(WsServerComposer));
            break;
        }

        default:
            LOG(ERROR)<<"WebSocket Protocol Not Support,Version is "<<version;
            return false;
    }

    AutoLock ll(mMutex);
    mClients->put(fd, data);
    return true;
}

WebSocketClientInfo _WebSocketClientManager::getClient(int fd) {
    AutoLock ll(mMutex);
    return mClients->get(fd);
}

void _WebSocketClientManager::setHttpHeader(int fd, HttpHeader h) {
    AutoLock ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->setHttpHeader(h);
}

void _WebSocketClientManager::setWebSocketHeader(int fd, WebSocketHeader h) {
    AutoLock ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->setWebSocketHeader(h);
}

void _WebSocketClientManager::setWebSocketPermessageDeflate(int fd, WebSocketPermessageDeflate v) {
    AutoLock ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->setDeflater(v);
}

void _WebSocketClientManager::setWebSocketProtocols(int fd,ArrayList<String> p) {
    AutoLock ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->setProtocols(p);
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
    mDefferedTaskMutex = createMutex();
    mPoolMutex = createMutex();
    mDefferedTasks = createLinkedList<DispatchData>();
    mPool = pool;
    mParser = createHttpV1Parser();
}

void _WebSocketDispatchRunnable::release() {
    AutoLock l(mPoolMutex);
    mPool = nullptr;
}

void _WebSocketDispatchRunnable::addDefferedTask(DispatchData data) {
    AutoLock l(mDefferedTaskMutex);
    mDefferedTasks->enQueueLast(data);
}

void _WebSocketDispatchRunnable::handleHttpData(DispatchData data) {

    int fd = data->fd;
    HttpPacket request = data->packet;
    HttpHeader header = request->getHeader();
    printf("handleHttpData trace1,request method is %d \n",request->getMethod());
    String upgrade = header->getValue(st(HttpHeader)::Upgrade);
    String key = header->getValue(st(HttpHeader)::SecWebSocketKey);
    String version = header->getValue(st(HttpHeader)::SecWebSocketVersion);
    printf("handleHttpData trace2 \n");
    if (upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
        printf("handleHttpData trace3 \n");
        // remove fd from http epoll
        mPool->getHttpV1Server()->deMonitor(fd);

        while(st(WebSocketClientManager)::getInstance()->getClient(fd)!= nullptr) {
            usleep(1000*5);
            LOG(INFO)<<"websocket client is not removed,fd is "<<fd;
        }
        st(WebSocketClientManager)::getInstance()->addClient(fd,
                                                            version->toBasicInt());
        st(WebSocketClientManager)::getInstance()->setHttpHeader(fd, header);

        WebSocketParser parser =
            st(WebSocketClientManager)::getInstance()->getClient(fd)->getParser();

        if (!parser->validateHandShake(header)) {
            printf("handleHttpData trace4 \n");
            return;
        }

        // Try to check whether extension support deflate.
        WebSocketPermessageDeflate deflate = parser->validateExtensions(header);
        if (deflate != nullptr) {
            st(WebSocketClientManager)::getInstance()->setWebSocketPermessageDeflate(
                fd, deflate);
        }
        printf("handleHttpData trace5 \n");
        ArrayList<String> protocols = parser->extractSubprotocols(header);
        if (protocols != nullptr && protocols->size() != 0) {
            LOG(ERROR)<<"Websocket Server Protocol is null";
        }

        WebSocketClientInfo client = st(WebSocketClientManager)::getInstance()->getClient(fd);
        mPool->getWebSocketServer()->monitor(fd);
        mPool->getWebSocketServer()->notifyConnect(client);
        printf("handleHttpData trace6 \n");
        WebSocketComposer composer = client->getComposer();
        ByteArray shakeresponse = composer->genShakeHandMessage(st(WebSocketClientManager)::getInstance()->getClient(fd));
        int ret = send(fd,shakeresponse->toValue(),shakeresponse->size(),0);
        printf("handleHttpData trace7 \n");
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

    WebSocketParser parser = client->getParser();
    WebSocketBuffer defferedBuff = client->getDefferedBuffer();
    if (defferedBuff != nullptr) {
        defferedBuff->mBuffer->append(pack);
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
            server->notifyMessage(client, msg);
        } else if (opcode == st(WebSocketProtocol)::OPCODE_BINARY) {
            if (header->isFinalFrame()) {
                ByteArray msgData = parser->parseContent(true);
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
                server->notifyData(client, out);
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

        st(WebSocketClientManager)::getInstance()
                ->getClient(fd)
                ->setDefferedBuffer(nullptr);
        break;
    }

FINISH:
    if(isRmClient) {
        st(WebSocketClientManager)::getInstance()->removeClient(client);
        server->notifyDisconnect(client);
    }
}

void _WebSocketDispatchRunnable::run() {
    bool isDoDefferedTask = false;
    printf("websocket run 1 \n");
    while(1) {
        DispatchData data = nullptr;
        {
            AutoLock l(mDefferedTaskMutex);
            data = mDefferedTasks->deQueueFirst();
            if(data != nullptr) {
                isDoDefferedTask = true;
                goto doAction;
            }
        }
        printf("websocket run 2 \n");
        {
            AutoLock l(mPoolMutex);
            if(isDoDefferedTask) {
                //clear fidmaps
                mPool->clearFds(mIndex);
            }

            isDoDefferedTask = false;
            data = mPool->getData(mIndex);
        }
        printf("websocket run 3 \n");
doAction:
        switch(data->cmd) {
            case st(DispatchData)::Http:
            printf("websocket run 4 \n");
            handleHttpData(data);
            break;

            case st(DispatchData)::Ws:
            printf("websocket run 5 \n");
            handleWsData(data);
            break;
        }
        printf("websocket run 6 \n");
    }
}

//----WebSocketDispatcherPool----
_WebSocketDispatcherPool::_WebSocketDispatcherPool(int threadnum) {
    fd2TidsMutex = createMutex("WebSocketDispatcherPool");

    datas = createBlockingLinkedList<DispatchData>();
    mExecutor = createThreadPoolExecutor(-1,threadnum);
    mRunnables = createArrayList<WebSocketDispatchRunnable>();
    for(int index = 0;index<threadnum;index++) {
        WebSocketDispatchRunnable r = createWebSocketDispatchRunnable(index,AutoClone(this));
        mExecutor->execute(r);
        mRunnables->add(r);
    }
}

void _WebSocketDispatcherPool::addData(DispatchData data) {
    datas->enQueueLast(data);
}

void _WebSocketDispatcherPool::setHttpV1Server(HttpV1Server server) {
    mHttpServer = server;
}

HttpV1Server _WebSocketDispatcherPool::getHttpV1Server() {
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
    ListIterator<WebSocketDispatchRunnable> iterator = mRunnables->getIterator();
    while(iterator->hasValue()) {
        WebSocketDispatchRunnable r = iterator->getValue();
        r->release();
        iterator->next();
    }

    mRunnables->clear();
}

DispatchData _WebSocketDispatcherPool::getData(int requireIndex) {
    while(1) {
        DispatchData data = datas->deQueueFirst();
        int runnableIndex = -1;
        {
            AutoLock l(fd2TidsMutex);
            auto iterator = fd2Tids.find(data->fd);
            if(iterator != fd2Tids.end()) {
                runnableIndex = iterator->second;
            }
        }

        if(runnableIndex != -1 && requireIndex != runnableIndex) {
            HttpDispatchRunnable runnable = mRunnables->get(runnableIndex);
            runnable->addDefferedTask(data);
            continue;
        }

        {
            AutoLock l(fd2TidsMutex);
            fd2Tids[data->fd] = requireIndex;
        }

        return data;
    }
}

void _WebSocketDispatcherPool::clearFds(int index) {
    for(auto it = fd2Tids.begin();it != fd2Tids.end();) {
        if(it->second == index) {
            it = fd2Tids.erase(it);
            continue;
        }
        it++;
    }
}


//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer() {
    mDispatchPool = createWebSocketDispatcherPool();
    mWsEpollObserver = createEPollFileObserver();
    mWsEpollObserver->start();
}

int _WebSocketServer::bind(String ip, int port, String path,
                           WebSocketListener listener) {
    if (mHttpServer != nullptr) {
      return -AlreadyExists;
    }

    mWsListener = listener;
    
    if (ip == nullptr) {
        mHttpServer = createHttpV1Server(port, AutoClone(this));
    } else {
        mHttpServer = createHttpV1Server(ip, port, AutoClone(this));
    }

    mDispatchPool->setHttpV1Server(mHttpServer);
    mDispatchPool->setWebSocketServer(AutoClone(this));

    return 0;
}

int _WebSocketServer::bind(int port, String path, WebSocketListener listener) {
    return bind(nullptr, port, path, listener);
}

void _WebSocketServer::monitor(int fd) {
    mWsEpollObserver->addObserver(fd,EPOLLIN | EPOLLRDHUP,AutoClone(this));
}

int _WebSocketServer::start() {
    return 0;
}

int _WebSocketServer::release() {
    //TODO
    mWsEpollObserver->release();
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

void _WebSocketServer::onMessage(sp<_HttpV1ClientInfo> client,sp<_HttpV1ResponseWriter> w,HttpPacket msg) {
    //int cmd,int fd, uint32_t events,HttpPacket pack
    printf("message !!!! method is %d \n",msg->getMethod());
    //_DispatchData::_DispatchData(int cmd,int fd, uint32_t events,HttpPacket pack) {
    DispatchData data = createDispatchData(st(DispatchData)::Http,client->getClientFd(),0,msg);
    mDispatchPool->addData(data);
}

void _WebSocketServer::onConnect(sp<_HttpV1ClientInfo>) {
    //TODO
    printf("_WebSocketServer onConnect1 \n");
}

void _WebSocketServer::onDisconnect(sp<_HttpV1ClientInfo>) {
    //TODO
    printf("_WebSocketServer onConnect2 \n");
}

int _WebSocketServer::notifyMessage(sp<_WebSocketClientInfo> client,String message) {
    return mWsListener->onMessage(client,message);
}

int _WebSocketServer::notifyData(sp<_WebSocketClientInfo> client,ByteArray data) {
    return mWsListener->onData(client,data);
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
