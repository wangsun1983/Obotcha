#include "WebSocketServer.hpp"

#include <stdio.h>
#include <sys/epoll.h>

#include "Error.hpp"
#include "WebSocketProtocol.hpp"
#include "HttpClientInfo.hpp"
#include "WebSocketClientManager.hpp"
#include "WebSocketComposer.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"
#include "HttpServerBuilder.hpp"
#include "Inet4Address.hpp"

namespace obotcha {


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

_DispatchData::_DispatchData(uint64_t clientid,int cmd,int fd, uint32_t events,HttpPacket pack) {
    this->fd = fd;
    this->events = events;
    this->cmd = cmd;
    this->clientId = 0;
    this->packet = pack;
    this->clientId = clientid;
}

void _WebSocketDispatcherPool::handleHttpData(DispatchData data) {

    int fd = data->fd;
    HttpPacket request = data->packet;
    HttpHeader header = request->getHeader();
    String upgrade = header->getValue(st(HttpHeader)::Upgrade);
    String key = header->getValue(st(HttpHeader)::SecWebSocketKey);
    String version = header->getValue(st(HttpHeader)::SecWebSocketVersion);
    if (upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
        // remove fd from http epoll
        mHttpServer->deMonitor(fd);

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

        mWebSocketServer->monitor(fd);
        mWebSocketServer->notifyConnect(client);
        WebSocketComposer composer = client->getComposer();
        ByteArray shakeresponse = composer->genShakeHandMessage(client);
        int ret = send(fd,shakeresponse->toValue(),shakeresponse->size(),0);
        if(ret < 0) {
            LOG(ERROR)<<"Websocket Server send response fail,reason:"<<strerror(errno);
        }
    }
}

void _WebSocketDispatcherPool::handleWsData(DispatchData data) {

    uint32_t events = data->events;
    int fd = data->fd;
    ByteArray pack = data->data;
    bool isRmClient = false;

    WebSocketClientInfo client =
        st(WebSocketClientManager)::getInstance()->getClient(fd);

    WebSocketServer server = mWebSocketServer;
    
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

//----WebSocketDispatcherPool----
_WebSocketDispatcherPool::_WebSocketDispatcherPool(int threadnum) {
    mDataMutex = createMutex();
    mDataCondition = createCondition();
    datas = createLinkedList<DispatchData>();
    mExecutor = createThreadPoolExecutor(-1,threadnum);
    mTaskGroup = createArrayList<LinkedList<DispatchData>>();
    isStop = false;

    for(int index = 0;index < threadnum;index++) {
        mTaskGroup->add(createLinkedList<DispatchData>());
        GroupIdTofds[index] = -1;
        mExecutor->execute([](sp<_WebSocketDispatcherPool> pool,int num) {
            DispatchData data = nullptr;
            while(1) {
                {
                    data  = pool->getData(num);
                    if(data == nullptr) {
                        pool = nullptr;
                        return;
                    }
                }
                
                switch(data->cmd) {
                    case st(DispatchData)::Http:
                    pool->handleHttpData(data);
                    break;

                    case st(DispatchData)::Ws:
                    pool->handleWsData(data);
                    break;
                }
            }
        },AutoClone(this),index);
    }
}

void _WebSocketDispatcherPool::addData(DispatchData data) {
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

void _WebSocketDispatcherPool::setHttpServer(HttpServer server) {
    mHttpServer = server;
}

void _WebSocketDispatcherPool::setWebSocketServer(WebSocketServer w) {
    mWebSocketServer = w;
}


void _WebSocketDispatcherPool::release() {
    mExecutor->shutdown();
    isStop = true;
    mDataCondition->notifyAll();
    //mRunnables->clear();
}

int _WebSocketDispatcherPool::getGroupIdByFd(int fd) {
     //try to find an index
    for(int index = 0;index <mExecutor->getThreadsNum();index++) {
        if(GroupIdTofds[index] == fd) {
            return index;
        }
    }

    return -1;
}

DispatchData _WebSocketDispatcherPool::getData(int requireIndex) {
    DispatchData data = nullptr;
    while(!isStop) {
        AutoLock l(mDataMutex);
        {
            //search deffered tasks
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
            
        }
        mDataCondition->wait(mDataMutex);
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
    //TODO
    InetAddress addr = createInet4Address(ip,port);

    mHttpServer = createHttpServerBuilder()
                ->setAddress(addr)
                ->setListener(AutoClone(this))
                ->build();

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
    return 0;
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
    //DispatchData data = createDispatchData(client->getClientId(),st(DispatchData)::Http,client->getClientFd(),0,msg);
    DispatchData data = createDispatchData(client->getSocket()->getFd(),st(DispatchData)::Http,client->getSocket()->getFd(),0,msg);
    
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
