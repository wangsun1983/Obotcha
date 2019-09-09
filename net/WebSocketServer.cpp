#include <sys/epoll.h>

#include "WebSocketServer.hpp"
#include "NetUtils.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketProtocol.hpp"
#include "TcpServer.hpp"
#include "Error.hpp"

namespace obotcha {

#define BUFF_SIZE 1024*128

_WebSocketHttpListener::_WebSocketHttpListener() {
    httpEpollfd == 0;
    mParser = createHttpParser();
    mResponse = createWebSocketFrameComposer(false);
}

void _WebSocketHttpListener::setHttpEpollFd(int fd) {
    httpEpollfd = fd;
}

void _WebSocketHttpListener::setWsEpollObserver(HashMap<String,EPollFileObserver> obs) {
    mWsObservers = obs;
}
    
void _WebSocketHttpListener::onAccept(int fd,String ip,int port,ByteArray pack) {
    //check whether is http requset for upgrage ws
    //TODO
    printf("onAccept content is %s \n",pack->toValue());
    String req = createString(pack->toValue(),0,pack->size());
    HttpPacket request = mParser->parseRequest(req);
    HttpHeader header = request->getHeader();

    String upgrade = header->getValue(Http_Header_Upgrade);
    String key = header->getValue(Http_Header_Sec_WebSocket_Key);
    String version = header->getValue(Http_Header_Sec_WebSocket_Version);
    String extensions = header->getValue(Http_Header_Sec_WebSocket_Extensions);
    //String path = header->getValue(Http_Header_Path);
    //String schema = header->getValue(Http_Header_Scheme);
    if(upgrade != nullptr) {
        printf("upgrade is %s \n",upgrade->toChars());
    }
    
    if(upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
        printf("websocket is !!!!!!!");
        //remove fd from http epoll
        st(NetUtils)::delEpollFd(httpEpollfd,fd);

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

}

void _WebSocketHttpListener::onConnect(int fd,String domain) {

}

//-----WebSocketEpollListener-----
_WebSocketEpollListener::_WebSocketEpollListener(WebSocketListener l) {
    mHybi13Parser = createWebSocketHybi13Parser();
    mWsSocketListener = l;
    mResponse = createWebSocketFrameComposer(false);
}

int _WebSocketEpollListener::onEvent(int fd,int events){
    if((events &EPOLLRDHUP) != 0) {
        printf("hangup sockfd!!!! fd is %d \n",fd);
        //epoll_ctl(mEpollfd, EPOLL_CTL_DEL, sockfd, NULL);
        return EPollOnEventResultRemoveFd;
    }

    printf("Event is %d \n",events);

    char recv_buf[BUFF_SIZE];
    int len = recv(fd, recv_buf, BUFF_SIZE, 0);
    printf("len is %d \n",len);
    if(len == BUFF_SIZE) {
        printf("error!!!!!! buff is oversize \n");
    }
    
    ByteArray pack = createByteArray(recv_buf,len);
    ByteArray continuePack;
    int readIndex = 0;
    while(1) {
        mHybi13Parser->setParseData(pack);
        WebSocketHeader header = mHybi13Parser->parseHeader();
        int framesize = header->getFrameLength();
        int headersize = header->getHeadSize();
        int opcode = header->getOpCode();
        printf("framesize is %d,headersize is %d,opcode is %d \n",framesize,headersize,opcode);

        if(opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
            ByteArray msgData = mHybi13Parser->parseContent();
            String msg = msgData->toString();
            printf("recv websocket from client msg is %s,fd is %d \n",msg->toChars(),fd);
            mWsSocketListener->onMessage(fd,msg);
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            printf("on ping start !!! \n");
            ByteArray buff = mHybi13Parser->parsePingBuff();
            if(mWsSocketListener->onPing(fd,buff->toString()) == PingResultResponse) {
                ByteArray resp = mResponse->generateControlFrame(st(WebSocketProtocol)::OPCODE_CONTROL_PONG,
                                            buff);
                st(NetUtils)::sendTcpPacket(fd,resp);
            }
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            //TODO
            printf("OPCODE_CONTROL_PONG \n");
            ByteArray pong = mHybi13Parser->parsePongBuff();
            String msg = pong->toString();
            mWsSocketListener->onPong(fd,msg);

        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            printf("OPCODE_CONTROL_CLOSE \n");
            return EPollOnEventResultRemoveFd;
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
            //TODO
            printf("OPCODE_CONTINUATION trace !!! \n");
            ByteArray msgData = mHybi13Parser->parseContent();
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
    mServer->start();
    //mEpollObserver->start();
}


}

