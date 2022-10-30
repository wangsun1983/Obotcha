#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>
#include <mutex>
#include <thread>


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
#include "HttpConnection.hpp"
#include "HttpStatus.hpp"
#include "NetEvent.hpp"


namespace obotcha {

SocketMonitor _WebSocketClient::mSocketMonitor = nullptr;

_WebSocketClient::_WebSocketClient(int version) {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        mSocketMonitor = createSocketMonitor();
    });
    
    //mVersion = version;
    mWsListener = nullptr;
    mHttpOption = nullptr;
    mOutputStream = nullptr;
    mSocket = nullptr;

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
            Trigger(InitializeException,"Websocket Client not support version!!!");
        }
    }
}


int _WebSocketClient::connect(String url,WebSocketListener l,HttpOption option) {
    //send http request
    HttpUrl httpUrl = createHttpUrl(url);
    mWsListener = l;
    HttpRequest shakeHandMsg = composer->genClientShakeHandMessage(httpUrl);
    HttpConnection connection = createHttpConnection(httpUrl);
    if(connection->connect() < 0) {
        return -1;
    }

    HttpResponse response = connection->execute(shakeHandMsg);
    
    if(response->getHeader()->getResponseStatus() == st(HttpStatus)::SwitchProtocls) {

        mSocket = connection->getSocket();

        mSocketMonitor->bind(mSocket,AutoClone(this));
       
        mOutputStream = mSocket->getOutputStream();
       
        String extentions = response->getHeader()->get(st(HttpHeader)::SecWebSocketExtensions);
        if(extentions != nullptr) {
            if(extentions->indexOf("sec-websocket-extensions") > 0) {
                composer->setDeflate(createWebSocketPermessageDeflate());
            }
        }
        
        return 0;
    }
    
    return -1;
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
    stream->close();

    return sendBinaryData(content);
}

int _WebSocketClient::_send(ArrayList<ByteArray> data) {
    if(mOutputStream == nullptr) {
        return -1;
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
        case st(NetEvent)::Message: {
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

                    case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE:
                        mSocketMonitor->unbind(mSocket);
                        mSocket->close();
                        mOutputStream->close();
                        //TODO?
                        //mSocketMonitor->close();
                    break;
                }

                iterator->next();
            }
        }

        case st(NetEvent)::Disconnect: {
            mWsListener->onDisconnect();
            break;
        }

        case st(NetEvent)::Connect: {
            mWsListener->onConnect();
            break;
        }

        default:
        break;
    }
}

void _WebSocketClient::close() {
    //send close message to server
    sendCloseMessage(createString("end"));
}

}


