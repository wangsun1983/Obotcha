#include <sys/epoll.h>
#include <stdio.h>

#include "WebSocketServer.hpp"
#include "NetUtils.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Parser.hpp"

#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi13Composer.hpp"

#include "WebSocketProtocol.hpp"
#include "TcpServer.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

#define TAG "WebSocketServer"

//--------------------WebSocketClientManager-----------------
WebSocketClientManager _WebSocketClientManager::mInstance = nullptr;
Mutex _WebSocketClientManager::mMutex = createMutex("WebSocketClientManagerMutex");

_WebSocketClientManager::_WebSocketClientManager() {
    mClients = createHashMap<int,WebSocketClientInfo>();
}

WebSocketClientManager _WebSocketClientManager::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mMutex);

    if(mInstance != nullptr) {
        return mInstance;
    }

    _WebSocketClientManager *v = new _WebSocketClientManager();
    mInstance.set_pointer(v);
    return mInstance;
}

bool _WebSocketClientManager::addClient(int fd,int version) {
    WebSocketClientInfo data = createWebSocketClientInfo();
    data->setClientFd(fd);

    switch(version) {
        case 0:{
            data->setParser(createWebSocketHybi00Parser());
            data->setComposer(createWebSocketHybi00Composer(WsServerComposer));
            break;
        }
        
        case 7:{
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
        LOGE(TAG,"WebSocket Protocol Not Support,Version is ",version);
        return false;
    }
    
    AutoLock ll(mMutex);
    mClients->put(fd,data);
    return true;
}

WebSocketClientInfo _WebSocketClientManager::getClient(int fd) {
    AutoLock ll(mMutex);
    return mClients->get(fd);
}
    
void _WebSocketClientManager::setHttpHeader(int fd,HttpHeader h) {
    AutoLock ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->setHttpHeader(h);
}

void _WebSocketClientManager::setWebSocketHeader(int fd,WebSocketHeader h) {
    AutoLock ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->setWebSocketHeader(h);
}

void _WebSocketClientManager::setWebSocketPermessageDeflate(int fd,WebSocketPermessageDeflate v) {
    AutoLock ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->setDeflater(v);
}

void _WebSocketClientManager::setWebSocketProtocols(int fd,ArrayList<String> p) {
    AutoLock ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->setProtocols(p);
}
    
void _WebSocketClientManager::removeClient(int fd) {
    AutoLock ll(mMutex);
    mClients->remove(fd);
}

//--------------------WebSocketHttpListener-----------------
_WebSocketHttpListener::_WebSocketHttpListener() {
    httpEpollfd = 0;
    mParser = createHttpV1Parser();
    mResponse = createWebSocketFrameComposer(false);
}

void _WebSocketHttpListener::setHttpEpollFd(int fd) {
    httpEpollfd = fd;
}

void _WebSocketHttpListener::onTimeout() {
    //TODO
}

void _WebSocketHttpListener::setWsEpollObserver(HashMap<String,EPollFileObserver> obs,WebSocketEpollListener l) {
    mWsObservers = obs;

    mEpollListener = l;
}
    
void _WebSocketHttpListener::onAccept(int fd,String ip,int port,ByteArray pack) {
    String req = pack->toString();
    HttpPacket request = mParser->parseEntireRequest(req);
    HttpHeader header = request->getHeader();

    String upgrade = header->getValue(st(HttpHeader)::Upgrade);
    String key = header->getValue(st(HttpHeader)::SecWebSocketKey);
    String version = header->getValue(st(HttpHeader)::SecWebSocketVersion);
    printf("upgrade is %s,key is %s,version is %s \n",upgrade->toChars(),key->toChars(),version->toChars());
    
    if(upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
        //remove fd from http epoll
        st(NetUtils)::delEpollFd(httpEpollfd,fd);
        printf("ws socket onAccept trace1 \n");
        
        st(WebSocketClientManager)::getInstance()->addClient(fd,version->toBasicInt());
        st(WebSocketClientManager)::getInstance()->setHttpHeader(fd,header);

        WebSocketParser parser = st(WebSocketClientManager)::getInstance()->getClient(fd)->getParser();

        if(!parser->validateHandShake(header)) {
            //invalid connection,we should close.
            //TODO
            printf("ws socket onAccept trace2 \n");
            return;
        }

        //Try to check whether extension support deflate.
        WebSocketPermessageDeflate deflate = parser->validateExtensions(header);
        if(deflate != nullptr) {
            st(WebSocketClientManager)::getInstance()->setWebSocketPermessageDeflate(fd,deflate);
        }
        
        ArrayList<String> protocols = parser->extractSubprotocols(header);
        if(protocols != nullptr && protocols->size() != 0) {
            //TODO
        }

        //add fd to ws epoll
        printf("ws socket onAccept trace2 \n");
        EPollFileObserver observer = mWsObservers->get(request->getUrl());
        if(observer != nullptr) {
            printf("ws socket onAccept trace3 \n");
            //observer->addFd(fd,EPOLLIN|EPOLLRDHUP|EPOLLHUP|EPOLLMSG|EPOLLET);
            observer->addObserver(fd,EPOLLIN|EPOLLRDHUP|EPOLLHUP|EPOLLMSG|EPOLLET,mEpollListener);
        } 

        //String shakeresponse = mResponse->generateShakeHandFrame(key);
        //WebSocketComposer composer = st(WebSocketClientManager)::getInstance()->getClient(fd)->getComposer;
        WebSocketClientInfo client = st(WebSocketClientManager)::getInstance()->getClient(fd);
        WebSocketComposer composer = client->getComposer();
        ByteArray shakeresponse = composer->genShakeHandMessage(st(WebSocketClientManager)::getInstance()->getClient(fd));
        printf("sendresponse is %s \n",shakeresponse->toString()->toChars());
        int ret = st(NetUtils)::sendTcpPacket(fd,shakeresponse);
        printf("send response result is %d \n",ret);
    }
    
}

void _WebSocketHttpListener::onDisconnect(int fd) {
    st(NetUtils)::delEpollFd(httpEpollfd,fd);
}

void _WebSocketHttpListener::onConnect(int fd,String ip,int port) {
    //Do Nothing
}

void _WebSocketHttpListener::onConnect(int fd,String domain) {
    //Do Nothing
}

//-----WebSocketEpollListener-----
_WebSocketEpollListener::_WebSocketEpollListener(WebSocketListener l) {
    //mHybi13Parser = createWebSocketHybi13Parser();
    mWsSocketListener = l;
    mResponse = createWebSocketFrameComposer(false);
    mRecvBuff = (byte*)malloc(WEBSOCKET_BUFF_SIZE);
}

_WebSocketEpollListener::~_WebSocketEpollListener() {
    free(mRecvBuff);
}

int _WebSocketEpollListener::onEvent(int fd,uint32_t events,ByteArray pack){
    printf("ws _WebSocketEpollListener onEvent \n");

    if((events &EPOLLRDHUP) != 0) {
        st(WebSocketClientManager)::getInstance()->removeClient(fd);
        return st(EPollFileObserver)::OnEventRemoveObserver;
    }

    //int len = recv(fd, mRecvBuff, WEBSOCKET_BUFF_SIZE, 0);
    //if(len == -1) {
    //    st(WebSocketClientManager)::getInstance()->removeClient(fd);
    //    return EPollOnEventResultRemoveFd;
    //} if(len == WEBSOCKET_BUFF_SIZE) {
    //    LOGE("WebSocket Receive Buffer Over Size");
    //}
    if(pack == nullptr || pack->size() == 0) {
        printf("ws _WebSocketEpollListener onEvent trace1\n");
        st(WebSocketClientManager)::getInstance()->removeClient(fd);
        return st(EPollFileObserver)::OnEventRemoveObserver;
    }

    int readIndex = 0;
    WebSocketParser parser = st(WebSocketClientManager)::getInstance()->getClient(fd)->getParser();
    //check pack
    WebSocketClientInfo client = st(WebSocketClientManager)::getInstance()->getClient(fd);

    while(1) {
        WebSocketEntireBuffer entireBuff = client->getEntireBuffer();
        if(entireBuff != nullptr) {
            entireBuff->mBuffer->append(pack);
            pack = entireBuff->mBuffer;
        }

        if(!parser->validateEntirePacket(pack)) {
            //it is not a full packet
            WebSocketEntireBuffer entireBuff = client->getEntireBuffer();
            if(entireBuff == nullptr) {
                entireBuff = createWebSocketEntireBuffer();
                entireBuff->mBuffer = pack;
                st(WebSocketClientManager)::getInstance()->getClient(fd)->setEntireBuffer(entireBuff);
            }
            break;
        }

        parser->setParseData(pack);
        WebSocketHeader header = parser->parseHeader();

        int opcode = header->getOpCode();
        int framesize = header->getFrameLength();
        int headersize = header->getHeadSize();
        
        if(opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
            ByteArray msgData = parser->parseContent(true);
            String msg = msgData->toString();
            mWsSocketListener->onMessage(client,msg);
        } else if(opcode == st(WebSocketProtocol)::OPCODE_BINARY) {
            if(header->isFinalFrame()) {
                ByteArray msgData = parser->parseContent(true);
            } else {
                ByteArray msgData = parser->parseContent(false);
                WebSocketContinueBuffer buff = createWebSocketContinueBuffer();
                buff->mBuffer = msgData;
                client->setContinueBuffer(buff);
            }
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            ByteArray buff = parser->parsePingBuff();
            if(mWsSocketListener->onPing(client,buff->toString()) == PingResultResponse) {
                ByteArray resp = mResponse->generateControlFrame(st(WebSocketProtocol)::OPCODE_CONTROL_PONG,
                                            buff);
                st(NetUtils)::sendTcpPacket(fd,resp);
            }
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            ByteArray pong = parser->parsePongBuff();
            String msg = pong->toString();
            mWsSocketListener->onPong(client,msg);
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            st(WebSocketClientManager)::getInstance()->removeClient(fd);
            return st(EPollFileObserver)::OnEventRemoveObserver;;
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
            ByteArray msgData = parser->parseContent(false);
            //st(WebSocketClientManager)::getInstance()->getClient(fd)->mBuffer->mConitnueBuff->append(msgData);
            WebSocketContinueBuffer continuebuff = client->getContinueBuffer();
            continuebuff->mBuffer->append(msgData);

            if(header->isFinalFrame()) {
                ByteArray out = parser->validateContinuationContent(client->getContinueBuffer()->mBuffer);
                mWsSocketListener->onData(client,out);
                continuebuff->mBuffer = nullptr;
            }
        }

        //check whether there are two ws messages received in one buffer!
        //len -= (framesize + headersize);
        int resetLength = pack->size() - (framesize + headersize);
        readIndex += (framesize + headersize);
        if(resetLength > 0) {
            byte *pdata = pack->toValue();
            pack = createByteArray(&pdata[readIndex],resetLength);
            continue;
        } 
        
        break;
    }

    return st(EPollFileObserver)::OnEventOK;
}

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer() {
    mEpollObservers = createHashMap<String,EPollFileObserver>();
}

int _WebSocketServer::bind(String ip,int port,String path,WebSocketListener listener) {
    if(mServer!= nullptr) {
        return -AlreadyExists;
    }

    mWsListener = listener;
    mHttpListener = createWebSocketHttpListener();
    if(ip == nullptr) {
        mServer = createTcpServer(port,mHttpListener);
    } else {
        mServer = createTcpServer(ip,port,mHttpListener);
    }
    
    mHttpListener->setHttpEpollFd(mServer->getTcpEpollfd());
    //mServer->start();
    mEpollListener = createWebSocketEpollListener(listener);
    
    EPollFileObserver mEpollObserver = createEPollFileObserver();
    mEpollObservers->put(path,mEpollObserver);

    mHttpListener->setWsEpollObserver(mEpollObservers,mEpollListener);

    return 0;
}

int _WebSocketServer::bind(int port,String path,WebSocketListener listener){
    return bind(nullptr,port,path,listener);
}

int _WebSocketServer::start() {
    return mServer->start();
    //mEpollObserver->start();
}

int _WebSocketServer::release() {
    mServer->release();
    //mEpollObservers
    MapIterator<String,EPollFileObserver> iterator = mEpollObservers->getIterator();
    while(iterator->hasValue()) {
        EPollFileObserver observer = iterator->getValue();
        observer->release();
        iterator->next();
    }
}


}

