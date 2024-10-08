#include "WebSocketClient.hpp"
#include "WebSocketProtocol.hpp"
#include "Log.hpp"
#include "HttpStatus.hpp"

#include "FileInputStream.hpp"
#include "Inspect.hpp"
#include "ForEveryOne.hpp"
#include "AutoLock.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

SocketMonitor _WebSocketClient::mSocketMonitor = nullptr;

_WebSocketClient::_WebSocketClient(int version):mVersion(version) {
    static std::once_flag s_flag;
    std::call_once(s_flag, []() {
        mSocketMonitor = SocketMonitor::New();
    });

    mWaitClose = CountDownLatch::New(1);

    mReader = WebSocketInputReader::New(version,st(WebSocketProtocol)::Model::Client);
    mInspector = WebSocketInspector::New(version);
}


int _WebSocketClient::connect(String url,WebSocketListener l,HttpOption option) {
    //send http request
    HttpUrl httpUrl = HttpUrl::New(url);
    mWsListener = l;
    mHttpOption = option;
    HttpRequest shakeHandMsg = mInspector->createClientShakeHandMessage(httpUrl);
    mConnection = HttpConnection::New(httpUrl,option);
    Inspect(mConnection->connect() < 0,-1)
    HttpResponse response = mConnection->execute(shakeHandMsg);
    if(response->getHeader()->getResponseStatus() 
            == st(HttpStatus)::SwitchProtocls) {
        mSocket = mConnection->getSocket();
        mSocketMonitor->bind(mSocket,AutoClone(this));
        mWriter = WebSocketOutputWriter::New(mVersion,st(WebSocketProtocol)::Model::Client,mSocket);
        auto extentions = response->getHeader()->getWebSocketExtensions();
        if(extentions != nullptr) {
            auto extensionLists = extentions->get();
            ForEveryOne(extension,extensionLists) {
                if(extension->contains("sec-websocket-extensions")) {
                    mWriter->setDeflate(WebSocketPermessageDeflate::New());
                    break;
                }
            }
        }

        AutoLock ll(mMutex);
        isConnected = true;
        return 0;
    }
    
    return -1;
}

long _WebSocketClient::sendTextMessage(String msg) {
    AutoLock l(mMutex);
    Inspect(!isConnected,-1)
    return mWriter->sendTextMessage(msg);
}

long _WebSocketClient::sendTextMessage(const char*msg) {
    AutoLock l(mMutex);
    Inspect(!isConnected,-1)
    return mWriter->sendTextMessage(String::New(msg));
}

long _WebSocketClient::sendPingMessage(ByteArray msg) {
    AutoLock l(mMutex);
    Inspect(!isConnected,-1)
    return mWriter->sendPingMessage(msg);
}

long _WebSocketClient::sendPongMessage(ByteArray msg) {
    AutoLock l(mMutex);
    Inspect(!isConnected,-1)
    return mWriter->sendPongMessage(msg);
}

long _WebSocketClient::sendCloseMessage(int status,ByteArray extraInfo) {
    AutoLock l(mMutex);
    Inspect(!isConnected,-1)
    return mWriter->sendCloseMessage(status,extraInfo);
}

long _WebSocketClient::sendBinaryMessage(ByteArray msg) {
    AutoLock l(mMutex);
    Inspect(!isConnected,-1)
    return mWriter->sendBinaryMessage(msg);
}

long _WebSocketClient::sendFile(File file) {
    FileInputStream stream = FileInputStream::New(file);
    stream->open();
    ByteArray content = stream->readAll();
    stream->close();

    return sendBinaryMessage(content);
}

void _WebSocketClient::onSocketMessage(st(Net)::Event event,Socket sockt,ByteArray pack) {
    switch(event) {
        case st(Net)::Event::Message: {
            ByteArray mPack = pack;
            mReader->push(mPack);
            ArrayList<WebSocketFrame> result = mReader->pull();
            ForEveryOne(frame,result) {
                switch(frame->getHeader()->getOpCode()) {
                    case st(WebSocketProtocol)::OPCODE_TEXT:{
                        mWsListener->onData(frame);
                    } break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_PING: {
                        if(st(WebSocket)::Response::Auto 
                            == mWsListener->onPing(frame->getData()->toString())) {
                                sendPingMessage(frame->getData());
                        }
                    } break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_PONG: {
                        mWsListener->onPong(frame->getData()->toString());
                    } break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE: {
                        AutoLock l(mMutex);
                        if(isConnected) {
                            mSocketMonitor->unbind(mSocket);
                            mSocket->close();
                            mWsListener->onDisconnect();
                            isConnected = false;
                            mWaitClose->countDown();
                        }
                    } break;

                    default:
                        LOG(ERROR)<<"WebSocketClient onSocketMessage unknow type:"<<frame->getHeader()->getOpCode();
                    break;
                }
            }
            break;
        }

        case st(Net)::Event::Disconnect: {
            AutoLock l(mMutex);
            if(isConnected) {
                mWsListener->onDisconnect();
                isConnected = false;
            }
            break;
        }

        case st(Net)::Event::Connect: {
            mWsListener->onConnect();
            break;
        }

        default:
            LOG(ERROR)<<"WebSocketClient onSocketMessage,unSupport event:"<<static_cast<int>(event);
        break;
    }
}

void _WebSocketClient::close() {
    sendCloseMessage();
    mWaitClose->await();
}

_WebSocketClient::~_WebSocketClient() {
    close();
}

}


