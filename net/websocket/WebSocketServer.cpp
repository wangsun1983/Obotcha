#include "WebSocketServer.hpp"

#include <stdio.h>
#include <sys/epoll.h>

#include "Error.hpp"
#include "Log.hpp"
#include "TcpServer.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketProtocol.hpp"
#include "Enviroment.hpp"
#include "CachePool.hpp"
#include "Log.hpp"

namespace obotcha {

#define TAG "WebSocketServer"

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
_DispatchData::_DispatchData(int cmd,int fd, uint32_t events,ByteArray pack) {
    this->fd = fd;
    this->events = events;
    if(pack != nullptr) {
        this->data = createByteArray(pack);
    } else {
        data = nullptr;
    }

    this->cmd = cmd;
}

//--------------------WebSocketDispatchThread-----------------
_WebSocketDispatchThread::_WebSocketDispatchThread(DispatchStatusListener m) {
    datas = createBlockingLinkedList<DispatchData>();
    mResponse = createWebSocketFrameComposer(false);
    mParser = createHttpV1Parser();
    mStatusListener = m;
    fds = createHashMap<int,int>();
}

void _WebSocketDispatchThread::add(DispatchData data) {
    datas->enQueueLast(data);
}

int _WebSocketDispatchThread::getWorkQueueSize() {
    return datas->size();
}

void _WebSocketDispatchThread::handleHttpData(DispatchData data) {

    int fd = data->fd;
    String req = data->data->toString();
    HttpPacket request = mParser->parseEntireRequest(req);
    HttpHeader header = request->getHeader();

    String upgrade = header->getValue(st(HttpHeader)::Upgrade);
    String key = header->getValue(st(HttpHeader)::SecWebSocketKey);
    String version = header->getValue(st(HttpHeader)::SecWebSocketVersion);
    if (upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
        // remove fd from http epoll
        data->mServerObserver->removeObserver(fd);
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
            return;
        }

        // Try to check whether extension support deflate.
        WebSocketPermessageDeflate deflate = parser->validateExtensions(header);
        if (deflate != nullptr) {
            st(WebSocketClientManager)::getInstance()->setWebSocketPermessageDeflate(
                fd, deflate);
        }

        ArrayList<String> protocols = parser->extractSubprotocols(header);
        if (protocols != nullptr && protocols->size() != 0) {
            LOG(ERROR)<<"Websocket Server Protocol is null";
        }

        EPollFileObserver observer = data->mWsObservers->get(request->getUrl());
        if (observer != nullptr) {
          observer->addObserver(fd, EPOLLIN | EPOLLRDHUP,
                                data->mEpollListener);
        }

        data->mEpollListener->onConnect(fd);
        WebSocketClientInfo client = st(WebSocketClientManager)::getInstance()->getClient(fd);
        WebSocketComposer composer = client->getComposer();
        ByteArray shakeresponse = composer->genShakeHandMessage(st(WebSocketClientManager)::getInstance()->getClient(fd));
        int ret = send(fd,shakeresponse->toValue(),shakeresponse->size(),0);
        if(ret < 0) {
            LOG(ERROR)<<"Websocket Server send response fail,reason:"<<strerror(errno);
        }
    }
}

void _WebSocketDispatchThread::handleWsData(DispatchData data) {

    uint32_t events = data->events;
    int fd = data->fd;
    ByteArray pack = data->data;
    bool isRmClient = false;

    WebSocketClientInfo client =
        st(WebSocketClientManager)::getInstance()->getClient(fd);
    
    if(client == nullptr) {
      //receive hungup before.
      return;
    }

    if((events & EPOLLRDHUP) != 0) {
        if(pack == nullptr || pack->size() == 0) {
            st(WebSocketClientManager)::getInstance()->removeClient(client);
            data->mWsSocketListener->onDisconnect(client);
            return;
        }

        isRmClient = true;
    }

    WebSocketParser parser = client->getParser();
    WebSocketEntireBuffer entireBuff = client->getEntireBuffer();
    if (entireBuff != nullptr) {
        entireBuff->mBuffer->append(pack);
        pack = entireBuff->mBuffer;
    }

    while (1) {
        int readIndex = 0;
        if (!parser->validateEntirePacket(pack)) {
            // it is not a full packet
            if (entireBuff == nullptr) {
            entireBuff = createWebSocketEntireBuffer();
            }

            entireBuff->mBuffer = pack;
            st(WebSocketClientManager)::getInstance()
                ->getClient(fd)
                ->setEntireBuffer(entireBuff);
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
            data->mWsSocketListener->onMessage(client, msg);
        } else if (opcode == st(WebSocketProtocol)::OPCODE_BINARY) {
            if (header->isFinalFrame()) {
                ByteArray msgData = parser->parseContent(true);
            } else {
                ByteArray msgData = parser->parseContent(false);
                WebSocketContinueBuffer buff = createWebSocketContinueBuffer();
                buff->mBuffer = msgData;
                client->setContinueBuffer(buff);
            }
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            ByteArray buff = parser->parsePingBuff();
            if (data->mWsSocketListener->onPing(client, buff->toString()) ==
                PingResultResponse) {
            ByteArray resp = mResponse->generateControlFrame(
                st(WebSocketProtocol)::OPCODE_CONTROL_PONG, buff);
            //st(NetUtils)::sendTcpPacket(fd, resp);
            send(fd,resp->toValue(),resp->size(),0);
            }
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            ByteArray pong = parser->parsePongBuff();
            String msg = pong->toString();
            data->mWsSocketListener->onPong(client, msg);
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            //st(WebSocketClientManager)::getInstance()->removeClient(client);
            //return;
            isRmClient = true;
            goto FINISH;
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
            ByteArray msgData = parser->parseContent(false);
            // st(WebSocketClientManager)::getInstance()->getClient(fd)->mBuffer->mConitnueBuff->append(msgData);
            WebSocketContinueBuffer continuebuff = client->getContinueBuffer();
            continuebuff->mBuffer->append(msgData);

            if (header->isFinalFrame()) {
            ByteArray out = parser->validateContinuationContent(
                client->getContinueBuffer()->mBuffer);
            data->mWsSocketListener->onData(client, out);
            continuebuff->mBuffer = nullptr;
            }
        }

        // check whether there are two ws messages received in one buffer!
        // len -= (framesize + headersize);
        int resetLength = (pack->size() - (framesize + headersize));
        //printf("resetLength is %d,framesize is %d,headersize is %d \n",resetLength,framesize,headersize);

        readIndex += (framesize + headersize);
        //printf("readIndex is %d \n",readIndex);

        if (resetLength > 0) {
            byte *pdata = pack->toValue();
            pack = createByteArray(&pdata[readIndex], resetLength);
            //printf("pdata[0] is %x,pdata[1] is %x \n",pdata[readIndex],pdata[readIndex+1]);
            continue;
        }

        st(WebSocketClientManager)::getInstance()
                ->getClient(fd)
                ->setEntireBuffer(nullptr);
        break;
    }

FINISH:
    if(isRmClient) {
        st(WebSocketClientManager)::getInstance()->removeClient(client);
        data->mWsSocketListener->onDisconnect(client);
    }
}

void _WebSocketDispatchThread::dump() {
    LOG(INFO)<<"thread is is "<<pthread_self();
}

void _WebSocketDispatchThread::run() {
    while (1) {

        mStatusListener->lockData();
        {
        //AutoLock l(mClearAddMutex);
        if(datas->size() == 0) {
            MapIterator<int,int>iterator = fds->getIterator();
            while(iterator->hasValue()) {
                mStatusListener->onComplete(iterator->getKey());
                iterator->next();
            }
            fds->clear();
        }
        }
        mStatusListener->unlockData();

        DispatchData data = datas->deQueueFirst();
        if (data->fd == -1) {
        return;
        }

        fds->put(data->fd,0);
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

//------------_WebSocketDispatchManager
_DispatchManager::_DispatchManager() {
    threadsNum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gWebSocketRcvThreadsNum,4);

    mMutex = createMutex("ws dispatch");
    fdmaps = createHashMap<int,Integer>();

    mThreads = createArrayList<WebSocketDispatchThread>();

    for(int i = 0;i < threadsNum;i++) {
        WebSocketDispatchThread thread = createWebSocketDispatchThread(AutoClone(this));
        mThreads->add(thread);
        thread->start();
    }
}

void _DispatchManager::dispatch(DispatchData data) {
    //DispatchData data = createDispatchData(st(DispatchData)::Ws,fd,events,pack);
    AutoLock ll(mMutex);
    Integer threadId = fdmaps->get(data->fd);
    if(threadId != nullptr) {
        int num = threadId->toValue();
        mThreads->get(num)->add(data);
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

    //mThreads->get(hit)->dump();
    fdmaps->put(data->fd,createInteger(hit));
    mThreads->get(hit)->add(data);
}

void _DispatchManager::onComplete(int fd) {
    AutoLock ll(mMutex);
    fdmaps->remove(fd);
}

void _DispatchManager::lockData() {
    mMutex->lock();
}

void _DispatchManager::unlockData() {
    mMutex->unlock();
}

//--------------------WebSocketHttpListener-----------------
_WebSocketHttpListener::_WebSocketHttpListener() {
    mDispatchMgr = createDispatchManager();
}

void _WebSocketHttpListener::setHttpEpollObserver(EPollFileObserver ob) {
    mServerObserver = ob;
}

void _WebSocketHttpListener::onTimeout() {
  // TODO
}

void _WebSocketHttpListener::setWsEpollObserver(
    HashMap<String, EPollFileObserver> obs, WebSocketEpollListener l) {
    mWsObservers = obs;
    mEpollListener = l;
}

void _WebSocketHttpListener::onDataReceived(SocketResponser r,ByteArray pack) {
    DispatchData data = createDispatchData(st(DispatchData)::Http,r->getFd(),0,pack);
    data->mServerObserver = mServerObserver;
    data->mWsObservers = mWsObservers;
    data->mEpollListener = mEpollListener;

    mDispatchMgr->dispatch(data);
}

void _WebSocketHttpListener::onDisconnect(SocketResponser r) {
    //st(NetUtils)::delEpollFd(httpEpollfd, r->getFd());
    //epoll_ctl(httpEpollfd, EPOLL_CTL_DEL, r->getFd(), NULL);
}

void _WebSocketHttpListener::onConnect(SocketResponser r) {
    //we should check whether ws client is not closed
}

//-----WebSocketEpollListener-----
_WebSocketEpollListener::_WebSocketEpollListener(WebSocketListener l) {
    // mHybi13Parser = createWebSocketHybi13Parser();
    mDispacher = createDispatchManager();
    mWsSocketListener = l;
}

_WebSocketEpollListener::~_WebSocketEpollListener() {
    //TODO
}

int _WebSocketEpollListener::onConnect(int fd) {
    WebSocketClientInfo client =
      st(WebSocketClientManager)::getInstance()->getClient(fd);
    mWsSocketListener->onConnect(client);
}

int _WebSocketEpollListener::onEvent(int fd, uint32_t events, ByteArray pack) {
    DispatchData data = createDispatchData(st(DispatchData)::Ws,fd,events,pack);
    data->mWsSocketListener = mWsSocketListener;

    mDispacher->dispatch(data);
    return st(EPollFileObserver)::OnEventOK;
}

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer() {
    mEpollObservers = createHashMap<String, EPollFileObserver>();
}

int _WebSocketServer::bind(String ip, int port, String path,
                           WebSocketListener listener) {
    if (mServer != nullptr) {
      return -AlreadyExists;
    }

    mWsListener = listener;
    mHttpListener = createWebSocketHttpListener();
    if (ip == nullptr) {
      mServer = createTcpServer(port, mHttpListener);
    } else {
      mServer = createTcpServer(ip, port, mHttpListener);
    }

    // mServer->start();
    mEpollListener = createWebSocketEpollListener(listener);

    EPollFileObserver mEpollObserver = createEPollFileObserver();
    mEpollObservers->put(path, mEpollObserver);

    mHttpListener->setWsEpollObserver(mEpollObservers, mEpollListener);

    return 0;
}

int _WebSocketServer::bind(int port, String path, WebSocketListener listener) {
    return bind(nullptr, port, path, listener);
}

int _WebSocketServer::start() {
    int ret = mServer->start();
    mHttpListener->setHttpEpollObserver(mServer->mObserver);
    return ret;
}

int _WebSocketServer::release() {
    mServer->release();
    // mEpollObservers
    MapIterator<String, EPollFileObserver> iterator =
        mEpollObservers->getIterator();
    while (iterator->hasValue()) {
        EPollFileObserver observer = iterator->getValue();
        observer->release();
        iterator->next();
    }
}

}  // namespace obotcha
