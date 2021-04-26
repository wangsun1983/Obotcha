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
#include "HttpUrlConnection.hpp"
#include "HttpStatus.hpp"


namespace obotcha {

#define TAG "WebSocketClient"

_WebSocketClient::_WebSocketClient(int version) {
    mVersion = version;
    mSocketMonitor = createSocketMonitor();
    //client message need use mask.
    //updateMask(true);

    parser = nullptr;
    composer = nullptr;

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
    mWsListener = l;
    printf("start connect \n");
    HttpRequest shakeHandMsg = composer->genClientShakeHandMessage(httpUrl);
    HttpUrlConnection connection = createHttpUrlConnection(httpUrl);
    if(connection->connect() < 0) {
        printf("connect fail \n");
        return -NetConnectFail;
    }

    HttpResponse response = connection->execute(shakeHandMsg);
    printf("connect trace1 \n");
    if(response->getHeader()->getResponseStatus() == st(HttpStatus)::SwitchProtocls) {
        printf("connect trace2 \n");
        mSocket = connection->getSocket();
        mSocketMonitor->bind(connection->getSocket(),AutoClone(this));
        mOutputStream = mSocket->getOutputStream();
        return 0;
    }
    
    return -NetConnectFail;
}

int _WebSocketClient::sendTextMessage(String msg) {
    return _send(composer->genTextMessage(msg));
}

int _WebSocketClient::sendTextMessage(const char*msg) {
    return _send(composer->genTextMessage(createString(msg)));
}

int _WebSocketClient::sendPingMessage(String msg) {
    return _send(composer->genPingMessage(msg));
}

int _WebSocketClient::sendPongMessage(String msg) {
    return _send(composer->genPongMessage(msg));
}

int _WebSocketClient::sendCloseMessage(String msg) {
    return _send(composer->genCloseMessage(msg));
}

int _WebSocketClient::sendBinaryData(ByteArray msg) {
    return _send(composer->genBinaryMessage(msg));
}

int _WebSocketClient::sendFile(File file) {
    FileInputStream stream = createFileInputStream(file);
    stream->open();
    ByteArray content = stream->readAll();
    return sendBinaryData(content);
}

int _WebSocketClient::_send(ArrayList<ByteArray> data) {
    if(mOutputStream == nullptr) {
        return -NetConnectFail;
    }

    ListIterator<ByteArray> iterator = data->getIterator();
    while(iterator->hasValue()) {
        ByteArray msg = iterator->getValue();
        mOutputStream->write(msg);
        iterator->next();
    }

    return 0;
}

int _WebSocketClient::_send(ByteArray data) {
    return mOutputStream->write(data);
}

void _WebSocketClient::onSocketMessage(int event,Socket sockt,ByteArray pack) {
    switch(event) {
        case Message: {
            int len = pack->size();
            int readIndex = 0;
            ByteArray mPack = pack;

            parser->pushParseData(mPack);
            ArrayList<WebSocketFrame> result = parser->doParse();
            
            ListIterator<WebSocketFrame> iterator = result->getIterator();
            while(iterator->hasValue()) {
                WebSocketFrame frame = iterator->getValue();
                switch(frame->getHeader()->getOpCode()) {
                    case st(WebSocketProtocol)::OPCODE_TEXT:
                    mWsListener->onData(frame);
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_PING:
                    mWsListener->onPing(frame->getData()->toString());
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:
                    mWsListener->onPong(frame->getData()->toString());
                    break;
                }

                iterator->next();
            }
        }

        case Disconnect: {
            mWsListener->onDisconnect();
            break;
        }

        case Connect: {
            mWsListener->onConnect();
            break;
        }

        default:
        break;
    }
}

void _WebSocketClient::close() {
    mSocketMonitor->release();
    mSocket->close();
}

}


