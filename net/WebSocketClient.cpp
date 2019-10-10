#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "AtomicInteger.hpp"
#include "Thread.hpp"
#include "TcpServer.hpp"
#include "WebSocketListener.hpp"
#include "SocketListener.hpp"
#include "EPollFileObserver.hpp"
#include "Mutex.hpp"
#include "HttpParser.hpp"
#include "WebSocketFrameComposer.hpp"
#include "WebSocketParser.hpp"
#include "HashMap.hpp"
#include "WebSocketClient.hpp"
#include "HttpUrl.hpp"
#include "HttpUrlParser.hpp"
#include "WebSocketProtocol.hpp"

namespace obotcha {


_WebSocketTcpClientListener::_WebSocketTcpClientListener(WebSocketListener l) {
    mWsListener = l;
    mHybi13Parser = createWebSocketHybi13Parser();
    mProtoclType = WsClientProtocolHttp;
    mHttpParser = createHttpParser();
}

void _WebSocketTcpClientListener::onTimeout() {
    //TODO
}
    
void _WebSocketTcpClientListener::onAccept(int fd,String ip,int port,ByteArray pack) {
    printf("11111111 client accept pack is %s \n",pack->toValue());

    if(mProtoclType == WsClientProtocolHttp) {
        HttpPacket req = mHttpParser->parseResponse(pack->toValue());
        printf("status code is %d \n",req->getStatusCode());
        if(req->getStatusCode() == HTTP_RESPONSE_SWITCHING_PROTOCLS) {
            mProtoclType = WsClientProtocolWebSocket;
        } else {
            mWsListener->onDisconnect(fd);
        }
        return;
    }

    mHybi13Parser->setParseData(pack);
    int len = pack->size();
    int readIndex = 0;
    ByteArray mPack = pack;

    while(1) {
        mHybi13Parser->setParseData(mPack);
        WebSocketHeader header = mHybi13Parser->parseHeader();
        int framesize = header->getFrameLength();
        int headersize = header->getHeadSize();
        int opcode = header->getOpCode();
        printf("framesize is %d,headersize is %d,opcode is %d \n",framesize,headersize,opcode);

        if(opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
            ByteArray msgData = mHybi13Parser->parseContent();
            String msg = msgData->toString();
            printf("recv websocket from client msg is %s,fd is %d \n",msg->toChars(),fd);
            mWsListener->onMessage(fd,msg);
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            printf("on ping start !!! \n");
            return;
            //TODO
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            //TODO
            printf("OPCODE_CONTROL_PONG \n");
            ByteArray pong = mHybi13Parser->parsePongBuff();
            String msg = pong->toString();
            printf("recv pong from client msg is %s,fd is %d \n",msg->toChars(),fd);
            
            mWsListener->onPong(fd,msg);
            return;

        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            printf("OPCODE_CONTROL_CLOSE \n");
            return;
            //TODO
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
            //TODO
            
        }

        len -= (framesize + headersize);
        readIndex += (framesize + headersize);
        if(len > 0) {
            printf("rest len is %d \n",len);
            mPack = createByteArray(&pack->toValue()[readIndex],len);
            continue;
        } 
        
        break;
    }

}

void _WebSocketTcpClientListener::onDisconnect(int fd) {

}

void _WebSocketTcpClientListener::onConnect(int fd,String ip,int port) {

}

void _WebSocketTcpClientListener::onConnect(int fd,String domain) {

}

_WebSocketClient::_WebSocketClient() {
    mComposer = createWebSocketFrameComposer(true);
}

int _WebSocketClient::bind(String url,WebSocketListener l) {
    //send http request
    //mObserver = createEPollFileObserver();
    HttpPacket request = createHttpPacket();
    request->setMethod(HttpMethodGet);
    
    HttpUrl httpUrl = st(HttpUrlParser)::parseUrl(url);
    //printf("httpUrl path is %s,url is %s \n",httpUrl->getHost()->toChars(),httpUrl->getPath()->toChars());
    //printf("port is %d \n",httpUrl->getPort());
    request->setUrl(httpUrl->getPath());
    request->setMajorVersion(1);
    request->setMinorVersion(1);

    String host = httpUrl->getHost()->append(":")->append(createString(httpUrl->getPort()));
    request->getHeader()->setValue(Http_Header_Host,host);

    request->getHeader()->setValue(Http_Header_Accept,"*/*");
    request->getHeader()->setValue(Http_Header_Accept_Language,"en-US,en;q=0.5");
    request->getHeader()->setValue(Http_Header_Accept_Encoding,"gzip, deflate");
    request->getHeader()->setValue(Http_Header_Sec_WebSocket_Version,"13");
    request->getHeader()->setValue(Http_Header_Origin,"null");
    request->getHeader()->setValue(Http_Header_Sec_WebSocket_Extensions,"permessage-deflate");
    request->getHeader()->setValue(Http_Header_Sec_WebSocket_Key,"fYbVEMSirecOe/q+edVT+w==");
    request->getHeader()->setValue(Http_Header_Connection,"keep-alive, Upgrade");
    request->getHeader()->setValue(Http_Header_Upgrade,"websocket");
    request->getHeader()->setValue(Http_Header_Pragma,"no-cache");
    request->getHeader()->setValue(Http_Header_Cache_Control,"no-cache");

    String shakeHandMsg = request->genHttpRequest();
    //printf("request is %s \n",shakeHandMsg->toChars());

    mListener = createWebSocketTcpClientListener(l);

    mTcpClient = createAsyncTcpClient(httpUrl->getHost(),httpUrl->getPort(),mListener);
    mTcpClient->start();

    mTcpClient->send(createByteArray(shakeHandMsg));


    return 0;
}

int _WebSocketClient::sendMessage(String msg) {
    mTcpClient->send(mComposer->generateMessageFrame(
        st(WebSocketProtocol)::OPCODE_TEXT,
        createByteArray(msg)));
}

int _WebSocketClient::sendPing(String msg) {
    mTcpClient->send(mComposer->generateControlFrame(
        st(WebSocketProtocol)::OPCODE_CONTROL_PING,
        createByteArray(msg)));
}


}


