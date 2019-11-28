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
#include "WebSocketClientInfo.hpp"
#include "HttpUrl.hpp"
#include "HttpUrlParser.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"

namespace obotcha {

#define TAG "WebSocketClient"

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
        HttpPacket req = mHttpParser->parseResponse(pack->toString());
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
            ByteArray msgData = mHybi13Parser->parseContent(true);
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

_WebSocketClient::_WebSocketClient(int version = 13) {
    mVersion = version;
    mClient = createWebSocketClientInfo();
    switch(version) {
        case 0:{
            mClient->mParser = createWebSocketHybi00Parser();
            mClient->mComposer = createWebSocketHybi00Composer(WsClientComposer);
            break;
        }
        
        case 7:{
            mClient->mParser = createWebSocketHybi07Parser();
            mClient->mComposer = createWebSocketHybi07Composer(WsClientComposer);
            break;
        }
        
        case 8: {
            mClient->mParser = createWebSocketHybi08Parser();
            mClient->mComposer = createWebSocketHybi08Composer(WsClientComposer);
            break;
        }

        case 13: {
            mClient->mParser = createWebSocketHybi13Parser();
            mClient->mComposer = createWebSocketHybi13Composer(WsClientComposer);
            break;
        }
        
        default:{
            throw createInitializeException("Websocket Client not support version!!!");
            break;
        }
    }
}

WebSocketClient _WebSocketClient::buildConnectInfo(int header,String value) {
    mClient->mHttpHeader->setValue(header,value);
    if(header == Http_Header_Sec_WebSocket_Extensions && value->contains("permessage-deflate")) {
        //mClient->mDeflate = createWebSocketPermessageDeflate();
        //we should config client size;
        ArrayList<String> list = value->trimAll()->split(";");
        if(list == nullptr){
            list = createArrayList<String>();
            list->add(value);
        }

        mClient->mDeflate = createWebSocketPermessageDeflate();
        mClient->mDeflate->fit(list);
    }
    WebSocketClient client;
    client.set_pointer(this);
    return client;
}

void _WebSocketClient::clearConnectInfo() {
    mClient->mHttpHeader->clear();
}

void _WebSocketClient::updateConnectInfo(int header,String value) {
    mClient->mHttpHeader->setValue(header,value);
}

int _WebSocketClient::connect(String url,WebSocketListener l) {
    //send http request
    //HttpPacket request = createHttpPacket();
    //request->setMethod(HttpMethodGet);
    mClient->mHttpHeader->setMethod(HttpMethodGet);
    mClient->mConnectUrl = url;

    String shakeHandMsg = mClient->mComposer->genShakeHandMessage(mClient);
    mListener = createWebSocketTcpClientListener(l);
    
    HttpUrl httpUrl = st(HttpUrlParser)::parseUrl(url);
    mTcpClient = createAsyncTcpClient(httpUrl->getHost(),httpUrl->getPort(),mListener);
    mTcpClient->start();

    mTcpClient->send(createByteArray(shakeHandMsg));
    return 0;
}

int _WebSocketClient::sendMessage(String msg) {
    String wsPacket = mClient->mComposer->genTextMessage(mClient,msg);
    return mTcpClient->send(createByteArray(wsPacket));
}

int _WebSocketClient::sendMessage(const char*msg) {
    String wsPacket = mClient->mComposer->genTextMessage(mClient,createString(msg));
    return mTcpClient->send(createByteArray(wsPacket));
}

int _WebSocketClient::sendPing(String msg) {
#if 0    
    return mTcpClient->send(mComposer->generateControlFrame(
        st(WebSocketProtocol)::OPCODE_CONTROL_PING,
        createByteArray(msg)));
#endif        
}

int _WebSocketClient::sendByteArray(ByteArray) {
    //TODO
    return 0;
}

int _WebSocketClient::sendFile(File) {
    //TODO
    return 0;
}


}


