#include <sys/epoll.h>

#include "WebSocketServer.hpp"
#include "NetUtils.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketProtocol.hpp"

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
    HttpRequest request = mParser->parseRequest(req);
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
    printf("wal[0] is %d \n",recv_buf[0]&0xff);
    printf("wal[1] is %d \n",recv_buf[1]&0xff);
    printf("wal[2] is %d \n",recv_buf[2]&0xff);
    printf("wal[3] is %d \n",recv_buf[3]&0xff);

    ByteArray pack = createByteArray(recv_buf,len);
    mHybi13Parser->setParseData(pack);
    WebSocketHeader header = mHybi13Parser->parseHeader();
    //if(header == nullptr) {
    //    return;
    //}

    int opcode = header->getOpCode();

    if(opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
        String msg = mHybi13Parser->parseMessage();
        printf("recv websocket from client msg is %s,fd is %d \n",msg->toChars(),fd);
        mWsSocketListener->onMessage(fd,msg);
    } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
        printf("on ping start !!! \n");
        if(mWsSocketListener->onPing(fd) == PingResultResponse) {
            printf("on ping trace !!! \n");
            ByteArray buff = mHybi13Parser->parsePingBuff();
            ByteArray resp = mResponse->generateControlFrame(st(WebSocketProtocol)::OPCODE_CONTROL_PONG,
                                            buff);
            st(NetUtils)::sendTcpPacket(fd,resp);
        }
    } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
        //TODO
        mWsSocketListener->onPong(fd);

    } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
        //TODO
    }

    return EPollOnEventResultOK;
}

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer() {
    mEpollObservers = createHashMap<String,EPollFileObserver>();
}

int _WebSocketServer::bind(String ip,int port,String path,WebSocketListener listener) {
    if(mServer!= nullptr) {
        return -WebSocketServerFailAlreadBind;
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
}

int _WebSocketServer::bind(int port,String path,WebSocketListener listener) {
    if(mServer != nullptr) {
        return -WebSocketServerFailAlreadBind;
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
}

int _WebSocketServer::start() {
    mServer->start();
    //mEpollObserver->start();
}


}

