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
#include "FileInputStream.hpp"

namespace obotcha {

#define TAG "WebSocketClient"

_WebSocketTcpClientListener::_WebSocketTcpClientListener(WebSocketListener l,WebSocketClientInfo info) {
    mWsListener = l;
    mClient = info;
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
            mWsListener->onDisconnect(mClient);
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
            mWsListener->onMessage(mClient,msg);
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
            
            mWsListener->onPong(mClient,msg);
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
    mClient->setClientFd(fd);
}

void _WebSocketTcpClientListener::onConnect(int fd,String domain) {

}

_WebSocketClient::_WebSocketClient(int version = 13) {
    mVersion = version;
    mClient = createWebSocketClientInfo();
    switch(version) {
        case 0:{
            mClient->setParser(createWebSocketHybi00Parser());
            mClient->setComposer(createWebSocketHybi00Composer(WsClientComposer));
            break;
        }
        
        case 7:{
            mClient->setParser(createWebSocketHybi07Parser());
            mClient->setComposer(createWebSocketHybi07Composer(WsClientComposer));
            break;
        }
        
        case 8: {
            mClient->setParser(createWebSocketHybi08Parser());
            mClient->setComposer(createWebSocketHybi08Composer(WsClientComposer));
            break;
        }

        case 13: {
            mClient->setParser(createWebSocketHybi13Parser());
            mClient->setComposer(createWebSocketHybi13Composer(WsClientComposer));
            break;
        }
        
        default:{
            throw createInitializeException("Websocket Client not support version!!!");
            break;
        }
    }
}

WebSocketClient _WebSocketClient::buildConnectInfo(int header,String value) {
    HttpHeader httpHeader = mClient->getHttpHeader();
    httpHeader->setValue(header,value);

    if(header == Http_Header_Sec_WebSocket_Extensions && value->contains("permessage-deflate")) {
        //mClient->mDeflate = createWebSocketPermessageDeflate();
        //we should config client size;
        ArrayList<String> list = value->trimAll()->split(";");
        if(list == nullptr){
            list = createArrayList<String>();
            list->add(value);
        }

        WebSocketPermessageDeflate defalter = createWebSocketPermessageDeflate();
        defalter->fit(list);
        mClient->setDeflater(defalter);
    }

    WebSocketClient client;
    client.set_pointer(this);
    return client;
}

void _WebSocketClient::clearConnectInfo() {
    mClient->getHttpHeader()->clear();
}

void _WebSocketClient::updateConnectInfo(int header,String value) {
    mClient->getHttpHeader()->setValue(header,value);
}

int _WebSocketClient::connect(String url,WebSocketListener l) {
    //send http request
    //HttpPacket request = createHttpPacket();
    //request->setMethod(HttpMethodGet);
    mClient->getHttpHeader()->setMethod(HttpMethodGet);
    mClient->setConnectUrl(url);

    WebSocketComposer composer = mClient->getComposer();
    ByteArray shakeHandMsg = composer->genShakeHandMessage(mClient);
    mListener = createWebSocketTcpClientListener(l,mClient);
    
    HttpUrl httpUrl = st(HttpUrlParser)::parseUrl(url);
    mTcpClient = createAsyncTcpClient(httpUrl->getHost(),httpUrl->getPort(),mListener);
    mTcpClient->start();

    mTcpClient->send(shakeHandMsg);
    return 0;
}

int _WebSocketClient::sendMessage(String msg) {
    WebSocketComposer composer = mClient->getComposer();
    ArrayList<ByteArray> wsPacket = composer->genTextMessage(mClient,msg);
    printf("wsPacket size is %d \n",wsPacket->size());

    ListIterator<ByteArray> iterator = wsPacket->getIterator();
    int size = 0;

    while(iterator->hasValue()) {
        ByteArray data = iterator->getValue();
        int sendSize = mTcpClient->send(data);
        printf("sendSize is %d \n",sendSize);
        size += sendSize;
        iterator->next();
    }

    return size;
}

int _WebSocketClient::sendMessage(const char*msg) {
    return sendMessage(createString(msg));
}

int _WebSocketClient::sendPing(String msg) {
#if 0    
    return mTcpClient->send(mComposer->generateControlFrame(
        st(WebSocketProtocol)::OPCODE_CONTROL_PING,
        createByteArray(msg)));
#endif        
}

int _WebSocketClient::sendBinaryData(ByteArray data) {
    //ArrayList<ByteArray> wsPacket = mClient->mComposer->genBinaryMessage(mClient,data);
    WebSocketComposer composer = mClient->getComposer();
    ArrayList<ByteArray> wsPacket = composer->genBinaryMessage(mClient,data);
    printf("wsPacket111 size is %d \n",wsPacket->size());

    ListIterator<ByteArray> iterator = wsPacket->getIterator();
    //int size = 0;
    while(iterator->hasValue()) {
        ByteArray data = iterator->getValue();
        int size = mTcpClient->send(data);
        printf("send size is %d \n",size);
        sleep(1);
        iterator->next();
    }

    return 0;
}

int _WebSocketClient::sendFile(File file) {
    FileInputStream stream = createFileInputStream(file);
    stream->open();
    ByteArray content = stream->readAll();
    return sendBinaryData(content);
}


}


