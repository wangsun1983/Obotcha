#include <sys/epoll.h>
#include <stdio.h>

#include "WebSocketServer.hpp"
#include "NetUtils.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketProtocol.hpp"
#include "TcpServer.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

#define BUFF_SIZE 1024*512

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

    AutoMutex ll(mMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    //mInstance = createWebSocketClientManager();
    _WebSocketClientManager *v = new _WebSocketClientManager();
    mInstance.set_pointer(v);
    return mInstance;
}

bool _WebSocketClientManager::addClient(int fd,int version) {
    WebSocketClientInfo data = createWebSocketClientInfo();
    printf("addClient version is %d !!!!!!!",version);
    
    switch(version) {
        case 0:{
            data->mParser = createWebSocketHybi00Parser();
            break;
        }
        
        case 7:{
            data->mParser = createWebSocketHybi07Parser();
            break;
        }
        
        case 8: {
            data->mParser = createWebSocketHybi08Parser();
            break;
        }

        case 13: {
            data->mParser = createWebSocketHybi13Parser();
            break;
        }
        
        default:
        LOGE(TAG,"WebSocket Protocol Not Support,Version is ",version);
        return false;
    }
    
    AutoMutex ll(mMutex);
    mClients->put(fd,data);
    return true;
}

WebSocketClientInfo _WebSocketClientManager::getClient(int fd) {
    AutoMutex ll(mMutex);
    return mClients->get(fd);
}
    
void _WebSocketClientManager::setHttpHeader(int fd,HttpHeader h) {
    AutoMutex ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->mHttpHeader = h;
}

void _WebSocketClientManager::setWebSocketHeader(int fd,WebSocketHeader h) {
    AutoMutex ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->mWsHeader = h;
}

void _WebSocketClientManager::setWebSocketPermessageDeflate(int fd,WebSocketPermessageDeflate v) {
    AutoMutex ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->mDeflate = v;
}

void _WebSocketClientManager::setWebSocketProtocols(int fd,ArrayList<String> p) {
    AutoMutex ll(mMutex);
    WebSocketClientInfo data = mClients->get(fd);
    data->mProtocols = p;
}
    
void _WebSocketClientManager::removeClient(int fd) {
    AutoMutex ll(mMutex);
    mClients->remove(fd);
}

//--------------------WebSocketHttpListener-----------------
_WebSocketHttpListener::_WebSocketHttpListener() {
    httpEpollfd = 0;
    mParser = createHttpParser();
    mResponse = createWebSocketFrameComposer(false);
}

void _WebSocketHttpListener::setHttpEpollFd(int fd) {
    httpEpollfd = fd;
}

void _WebSocketHttpListener::onTimeout() {
    //TODO
}

void _WebSocketHttpListener::setWsEpollObserver(HashMap<String,EPollFileObserver> obs) {
    mWsObservers = obs;
}
    
void _WebSocketHttpListener::onAccept(int fd,String ip,int port,ByteArray pack) {
    String req = pack->toString();
    HttpPacket request = mParser->parseRequest(req);
    HttpHeader header = request->getHeader();

    String upgrade = header->getValue(Http_Header_Upgrade);
    String key = header->getValue(Http_Header_Sec_WebSocket_Key);
    String version = header->getValue(Http_Header_Sec_WebSocket_Version);
    
    if(upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
        printf("websocket is !!!!!!!");
        //remove fd from http epoll
        st(NetUtils)::delEpollFd(httpEpollfd,fd);
        
        st(WebSocketClientManager)::getInstance()->addClient(fd,version->toBasicInt());
        st(WebSocketClientManager)::getInstance()->setHttpHeader(fd,header);

        WebSocketParser parser = st(WebSocketClientManager)::getInstance()->getClient(fd)->mParser;

        if(!parser->validateHandShake(header)) {
            return;
        }

        WebSocketPermessageDeflate deflate = parser->validateExtensions(header);
        if(deflate == nullptr) {
            st(WebSocketClientManager)::getInstance()->setWebSocketPermessageDeflate(fd,deflate);
        }

        ArrayList<String> protocols = parser->extractSubprotocols(header);
        if(protocols != nullptr && protocols->size() != 0) {

        }

        //add fd to ws epoll
        printf("request get url is %s \n",request->getUrl()->toChars());

        EPollFileObserver observer = mWsObservers->get(request->getUrl());
        if(observer != nullptr) {
            observer->addFd(fd,EPOLLIN|EPOLLRDHUP|EPOLLHUP|EPOLLMSG|EPOLLET);
        } 

        String shakeresponse = mResponse->generateShakeHandFrame(key);
        printf("shakeresponse is %s \n",shakeresponse->toChars());
        st(NetUtils)::sendTcpPacket(fd,createByteArray(shakeresponse));
    }
    
}

void _WebSocketHttpListener::onDisconnect(int fd) {
    printf("websocket http listener disconnect \n");
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
}

int _WebSocketEpollListener::onEvent(int fd,int events){
    if((events &EPOLLRDHUP) != 0) {
        printf("hangup sockfd!!!! fd is %d \n",fd);
        st(WebSocketClientManager)::getInstance()->removeClient(fd);
        return EPollOnEventResultRemoveFd;
    }

    printf("Event is %d \n",events);

    char recv_buf[BUFF_SIZE];
    int len = recv(fd, recv_buf, BUFF_SIZE, 0);
    printf("len is %d \n",len);
    if(len == -1) {
        st(WebSocketClientManager)::getInstance()->removeClient(fd);
        return EPollOnEventResultRemoveFd;
    } if(len == BUFF_SIZE) {
        LOGE("WebSocket Receive Buffer Over Size");
        //TODO
    }
    
    ByteArray pack = createByteArray(recv_buf,len);
    ByteArray continuePack;
    int readIndex = 0;
    WebSocketParser parser = st(WebSocketClientManager)::getInstance()->getClient(fd)->mParser;
    while(1) {
        parser->setParseData(pack);
        WebSocketHeader header = parser->parseHeader();
        int framesize = header->getFrameLength();
        int headersize = header->getHeadSize();
        int opcode = header->getOpCode();
        printf("framesize is %d,headersize is %d,opcode is %d \n",framesize,headersize,opcode);

        if(opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
            ByteArray msgData = parser->parseContent();
            String msg = msgData->toString();
            printf("recv websocket from client msg is %s,fd is %d \n",msg->toChars(),fd);
            mWsSocketListener->onMessage(fd,msg);
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            printf("on ping start !!! \n");
            ByteArray buff = parser->parsePingBuff();
            if(mWsSocketListener->onPing(fd,buff->toString()) == PingResultResponse) {
                ByteArray resp = mResponse->generateControlFrame(st(WebSocketProtocol)::OPCODE_CONTROL_PONG,
                                            buff);
                st(NetUtils)::sendTcpPacket(fd,resp);
            }
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            //TODO
            printf("OPCODE_CONTROL_PONG \n");
            ByteArray pong = parser->parsePongBuff();
            String msg = pong->toString();
            mWsSocketListener->onPong(fd,msg);
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            printf("OPCODE_CONTROL_CLOSE \n");
            st(WebSocketClientManager)::getInstance()->removeClient(fd);
            return EPollOnEventResultRemoveFd;
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
            //TODO
            printf("OPCODE_CONTINUATION trace !!! \n");
            ByteArray msgData = parser->parseContent();
            continuePack->append(msgData);
        }

        len -= (framesize + headersize);
        readIndex += (framesize + headersize);
        if(len > 0) {
            printf("rest len is %d \n",len);
            pack = createByteArray(&recv_buf[readIndex],len);
            continue;
        } 
        
        break;
    }

    return EPollOnEventResultOK;
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
    mServer = createTcpServer(ip,port,mHttpListener);
    mHttpListener->setHttpEpollFd(mServer->getTcpEpollfd());
    //mServer->start();
    mEpollListener = createWebSocketEpollListener(listener);
    
    EPollFileObserver mEpollObserver = createEPollFileObserver(mEpollListener);
    mEpollObservers->put(path,mEpollObserver);

    mHttpListener->setWsEpollObserver(mEpollObservers);

    mEpollObserver->start();

    return 0;
}

int _WebSocketServer::bind(int port,String path,WebSocketListener listener) {
    if(mServer != nullptr) {
        return -AlreadyExists;
    }

    mWsListener = listener;
    mHttpListener = createWebSocketHttpListener();
    mServer = createTcpServer(port,mHttpListener);
    mHttpListener->setHttpEpollFd(mServer->getTcpEpollfd());
    //mServer->start();
    mEpollListener = createWebSocketEpollListener(listener);
    
    EPollFileObserver mEpollObserver = createEPollFileObserver(mEpollListener);
    mEpollObservers->put(path,mEpollObserver);

    mHttpListener->setWsEpollObserver(mEpollObservers);

    mEpollObserver->start();

    return 0;
}

int _WebSocketServer::start() {
    return mServer->start();
    //mEpollObserver->start();

}

int _WebSocketServer::release() {
    printf("websocket release trace1 \n");
    mServer->release();
    printf("websocket release trace2 \n");
    //mEpollObservers
    MapIterator<String,EPollFileObserver> iterator = mEpollObservers->getIterator();
    while(iterator->hasValue()) {
        EPollFileObserver observer = iterator->getValue();
        observer->release();
        iterator->next();
    }
    printf("websocket release trace3 \n");
}


}

