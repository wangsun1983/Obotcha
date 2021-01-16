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
#include "Thread.hpp"
#include "TcpServer.hpp"
#include "WebSocketListener.hpp"
#include "SocketListener.hpp"
#include "EPollFileObserver.hpp"
#include "Mutex.hpp"
#include "HttpResponseParser.hpp"
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
    mHttpParser = createHttpResponseParser();
}

void _WebSocketTcpClientListener::onTimeout() {
    //TODO
}
    
void _WebSocketTcpClientListener::onDataReceived(SocketResponser r,ByteArray pack) {
    /*
    if(mProtoclType == WsClientProtocolHttp) {
        HttpPacket req = mHttpParser->parseEntireResponse(pack->toString());
        if(req->getStatusCode() == st(HttpResponse)::SwitchProtocls) {
            mProtoclType = WsClientProtocolWebSocket;
            mClient->setClientFd(r->getFd());
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
        
        if(opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
            ByteArray msgData = mHybi13Parser->parseContent(true);
            String msg = msgData->toString();
            mWsListener->onMessage(mClient,msg);
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            return;
            //TODO
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            //TODO
            ByteArray pong = mHybi13Parser->parsePongBuff();
            String msg = pong->toString();
            
            mWsListener->onPong(mClient,msg);
            return;

        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            return;
            //TODO
        } else if(opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
            //TODO
            
        }

        len -= (framesize + headersize);
        readIndex += (framesize + headersize);
        if(len > 0) {
            mPack = createByteArray(&pack->toValue()[readIndex],len);
            continue;
        } 
        
        break;
    }
 */
}

void _WebSocketTcpClientListener::onDisconnect(SocketResponser r) {

}

void _WebSocketTcpClientListener::onConnect(SocketResponser r) {
    
}

_WebSocketClient::_WebSocketClient(int version = 13) {
    mSendTimeout = -1;
    mRcvTimeout = -1;

    mVersion = version;
    mClient = createWebSocketClientInfo();
    //client message need use mask.
    updateMask(true);

    WebSocketParser parser = nullptr;
    WebSocketComposer composer = nullptr;

    switch(version) {
        case 0:{
            parser = createWebSocketHybi00Parser();
            composer = createWebSocketHybi00Composer(WsClientComposer);
            break;
        }
        
        case 7:{
            parser = createWebSocketHybi07Parser();
            composer = createWebSocketHybi07Composer(WsClientComposer);
            break;
        }
        
        case 8: {
            parser = createWebSocketHybi08Parser();
            composer = createWebSocketHybi08Composer(WsClientComposer);
            break;
        }

        case 13: {
            parser = createWebSocketHybi13Parser();
            composer = createWebSocketHybi13Composer(WsClientComposer);
            break;
        }
        
        default:{
            throw InitializeException("Websocket Client not support version!!!");
            break;
        }
    }

    //parser->setAsClient();
    mClient->setParser(parser);
    mClient->setComposer(composer);
}

void _WebSocketClient::setSendTimeout(long timeout) {
    mSendTimeout = timeout;
}

long _WebSocketClient::getSendTimeout() {
    return mSendTimeout;
}

void _WebSocketClient::setRcvTimeout(long timeout) {
    mRcvTimeout = timeout;
}

long _WebSocketClient::getRcvTimeout() {
    return mRcvTimeout;
}

WebSocketClient _WebSocketClient::buildConnectInfo(String header,String value) {
    HttpHeader httpHeader = mClient->getHttpHeader();
    httpHeader->setValue(header,value);

    if(header->equals(st(HttpHeader)::SecWebSocketExtensions) && value->contains("permessage-deflate")) {
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

    return AutoClone(this);
}

void _WebSocketClient::clearConnectInfo() {
    mClient->getHttpHeader()->clear();
}

void _WebSocketClient::updateMask(bool v) {
    //mClient->getWebSocketHeader()->setMasked(v);
}

void _WebSocketClient::updateConnectInfo(String header,String value) {
    mClient->getHttpHeader()->setValue(header,value);
}

int _WebSocketClient::connect(String url,WebSocketListener l) {
    //send http request
    //HttpPacket request = createHttpPacket();
    //request->setMethod(HttpMethodGet);
    mClient->getHttpHeader()->setMethod(st(HttpMethod)::Get);
    mClient->setConnectUrl(url);

    WebSocketComposer composer = mClient->getComposer();
    ByteArray shakeHandMsg = composer->genShakeHandMessage(mClient);
    mListener = createWebSocketTcpClientListener(l,mClient);
    
    HttpUrl httpUrl = st(HttpUrlParser)::parseUrl(url);
    mTcpClient = createTcpClient(httpUrl->getHost(),httpUrl->getPort(),mListener);
    mTcpClient->setRcvTimeout(mRcvTimeout);
    mTcpClient->setSendTimeout(mSendTimeout);
    
    mTcpClient->doConnect();

    mTcpClient->doSend(shakeHandMsg);
    return 0;
}

int _WebSocketClient::sendTextMessage(String msg) {
    return mClient->sendTextMessage(msg);
}

int _WebSocketClient::sendTextMessage(const char*msg) {
    return sendTextMessage(createString(msg));
}

int _WebSocketClient::sendPingMessage(ByteArray msg) {
    return mClient->sendPingMessage(msg);
}

int _WebSocketClient::sendCloseMessage(ByteArray msg) {
    return mClient->sendCloseMessage(msg);
}

WebSocketClientInfo _WebSocketClient::getClientInfo() {
    return mClient;
}

int _WebSocketClient::sendBinaryData(ByteArray data) {
    return mClient->sendBinaryMessage(data);
}

int _WebSocketClient::sendFile(File file) {
    FileInputStream stream = createFileInputStream(file);
    stream->open();
    ByteArray content = stream->readAll();
    return sendBinaryData(content);
}


}


