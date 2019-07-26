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
    mResponse = createWebSocketResponse();
}

void _WebSocketHttpListener::setHttpEpollFd(int fd) {
    httpEpollfd = fd;
}

void _WebSocketHttpListener::setWsEpollObserver(EPollFileObserver observer) {
    mWsObserver = observer;
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
    if(upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
        printf("websocket is !!!!!!!");
        //remove fd from http epoll
        st(NetUtils)::delEpollFd(httpEpollfd,fd);

        //add fd to ws epoll
        mWsObserver->addFd(fd,EPOLLIN|EPOLLRDHUP|EPOLLHUP|EPOLLMSG|EPOLLET);

        String shakeresponse = mResponse->generateShakeHandResponse(key);
        printf("shakeresponse is %s \n",shakeresponse->toChars());
        st(NetUtils)::sendTcpPacket(fd,createByteArray(shakeresponse));
    }
    
}

void _WebSocketHttpListener::onDisconnect(int fd) {
    st(NetUtils)::delEpollFd(httpEpollfd,fd);
}

void _WebSocketHttpListener::onConnect(int fd,String ip,int port) {

}

void _WebSocketHttpListener::onConnect(int fd,String domain) {

}

//-----WebSocketEpollListener-----
_WebSocketEpollListener::_WebSocketEpollListener() {
    mHybi13Parser = createWebSocketHybi13Parser();
}

void _WebSocketEpollListener::onEvent(int fd,int events){
    if(((events&EPOLLIN) != 0) 
        && ((events &EPOLLRDHUP) != 0)) {
        printf("hangup sockfd!!!! \n");
        //epoll_ctl(mEpollfd, EPOLL_CTL_DEL, sockfd, NULL);
        return;
    }

    char recv_buf[BUFF_SIZE];
    int len = recv(fd, recv_buf, BUFF_SIZE, 0);
    printf("wal is %s \n",recv_buf);
    ByteArray pack = createByteArray(recv_buf,len);
    mHybi13Parser->setParseData(pack);
    WebSocketHeader header = mHybi13Parser->parseHeader();
    int opcode = header->getOpCode();

    if(opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
        String msg = mHybi13Parser->parseMessage();
        printf("recv websocket from client msg is %s \n",msg->toChars());
    } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
        //TODO
    } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
        //TODO
    } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
        //TODO
    }
}

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer() {

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
    mEpollListener = createWebSocketEpollListener();
    mEpollObserver = createEPollFileObserver(mEpollListener);

    mHttpListener->setWsEpollObserver(mEpollObserver);

    //mServer->start();
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
    mEpollListener = createWebSocketEpollListener();
    mEpollObserver = createEPollFileObserver(mEpollListener);

    mHttpListener->setWsEpollObserver(mEpollObserver);
}

int _WebSocketServer::start() {
    mServer->start();
    mEpollObserver->start();
}


}

