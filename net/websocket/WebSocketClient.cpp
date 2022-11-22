#include "WebSocketClient.hpp"
#include "WebSocketProtocol.hpp"
#include "Log.hpp"
#include "HttpConnection.hpp"
#include "HttpStatus.hpp"
#include "NetEvent.hpp"
#include "FileInputStream.hpp"
#include "Inspect.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

SocketMonitor _WebSocketClient::mSocketMonitor = nullptr;

_WebSocketClient::_WebSocketClient(int version) {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        mSocketMonitor = createSocketMonitor();
    });
    
    mWsListener = nullptr;
    mHttpOption = nullptr;
    mSocket = nullptr;
    mReader = createWebSocketInputReader(version,st(WebSocketProtocol)::Client);
    mInspector = createWebSocketInspector(version);
    mVersion = version;
}


int _WebSocketClient::connect(String url,WebSocketListener l,HttpOption option) {
    //send http request
    HttpUrl httpUrl = createHttpUrl(url);
    mWsListener = l;
    HttpRequest shakeHandMsg = mInspector->createClientShakeHandMessage(httpUrl);
    HttpConnection connection = createHttpConnection(httpUrl);
    Inspect(connection->connect() < 0,-1);

    HttpResponse response = connection->execute(shakeHandMsg);

    if(response->getHeader()->getResponseStatus() 
            == st(HttpStatus)::SwitchProtocls) {
        mSocket = connection->getSocket();
        mSocketMonitor->bind(mSocket,AutoClone(this));
        mWriter = createWebSocketOutputWriter(mVersion,st(WebSocketProtocol)::Client,mSocket);

        auto extentions = response->getHeader()->getWebSocketExtensions();
        if(extentions != nullptr) {
            auto extensionLists = extentions->get();
            ForEveryOne(extension,extensionLists) {
                if(extension->contains("sec-websocket-extensions")) {
                    mWriter->setDeflate(createWebSocketPermessageDeflate());
                    break;
                }
            }
        }
        
        return 0;
    }
    
    return -1;
}

int _WebSocketClient::sendTextMessage(String msg) {
    return mWriter->sendTextMessage(msg);
}

int _WebSocketClient::sendTextMessage(const char*msg) {
    return mWriter->sendTextMessage(createString(msg));
}

int _WebSocketClient::sendPingMessage(ByteArray msg) {
    return mWriter->sendPingMessage(msg);
}

int _WebSocketClient::sendPongMessage(ByteArray msg) {
    return mWriter->sendPongMessage(msg);
}

int _WebSocketClient::sendCloseMessage(int status,ByteArray extraInfo) {
    return mWriter->sendCloseMessage(status,extraInfo);
}

int _WebSocketClient::sendBinaryMessage(ByteArray msg) {
    return mWriter->sendBinaryMessage(msg);
}

int _WebSocketClient::sendFile(File file) {
    FileInputStream stream = createFileInputStream(file);
    stream->open();
    ByteArray content = stream->readAll();
    stream->close();

    return sendBinaryMessage(content);
}

void _WebSocketClient::onSocketMessage(int event,Socket sockt,ByteArray pack) {
    switch(event) {
        case st(NetEvent)::Message: {
            int len = pack->size();
            int readIndex = 0;
            ByteArray mPack = pack;

            mReader->push(mPack);
            ArrayList<WebSocketFrame> result = mReader->pull();
            
            ListIterator<WebSocketFrame> iterator = result->getIterator();
            while(iterator->hasValue()) {
                WebSocketFrame frame = iterator->getValue();
                switch(frame->getHeader()->getOpCode()) {
                    case st(WebSocketProtocol)::OPCODE_TEXT:
                        mWsListener->onData(frame);
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_PING:
                        if(st(WebSocketListener)::AutoResponse 
                            == mWsListener->onPing(frame->getData()->toString())) {
                                sendPingMessage(frame->getData());
                        }
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:
                        mWsListener->onPong(frame->getData()->toString());
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE:
                        mSocketMonitor->unbind(mSocket);
                        mSocket->close();
                    break;
                }

                iterator->next();
            }
            break;
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
    sendCloseMessage();
}

}


