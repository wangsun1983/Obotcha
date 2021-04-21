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
#include "WebSocketListener.hpp"
#include "SocketListener.hpp"
#include "EPollFileObserver.hpp"
#include "Mutex.hpp"
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

_WebSocketClient::_WebSocketClient(int version = 13) {
    mVersion = version;
    //client message need use mask.
    //updateMask(true);

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
}


int _WebSocketClient::connect(String url,WebSocketListener l,HttpOption option) {
    //send http request
    HttpUrl httpUrl = st(HttpUrlParser)::parseUrl(url);

    ByteArray shakeHandMsg = composer->genShakeHandMessage(httpUrl);
    //mListener = createWebSocketTcpClientListener(l,mClient);
    
    
    //mTcpClient = createTcpClient(httpUrl->getHost(),httpUrl->getPort(),mListener);
    //mTcpClient->setRcvTimeout(mRcvTimeout);
    //mTcpClient->setSendTimeout(mSendTimeout);
    
    //mTcpClient->doConnect();

    //mTcpClient->doSend(shakeHandMsg);
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


