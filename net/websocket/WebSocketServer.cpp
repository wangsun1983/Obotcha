#include "WebSocketServer.hpp"

#include <stdio.h>
#include <sys/epoll.h>

#include "Error.hpp"
#include "WebSocketProtocol.hpp"
#include "HttpLinker.hpp"
#include "WebSocketLinkerManager.hpp"
#include "WebSocketComposer.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"
#include "HttpServerBuilder.hpp"
#include "HttpOption.hpp"

namespace obotcha {

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer(int threadnum) {
    mSocketMonitor = createSocketMonitor(threadnum);
    mHttpServer = nullptr;
    mWsListeners = createHashMap<String,WebSocketListener>();
    mLinkerManager = createWebSocketLinkerManager();
}

int _WebSocketServer::bind(String path,WebSocketListener l) {
    mWsListeners->put(path,l);
    return 0;
}

int _WebSocketServer::start() {
    if(mHttpServer == nullptr) {
        mHttpServer = createHttpServerBuilder()
                    ->setAddress(mAddress)
                    ->setListener(AutoClone(this))
                    ->setOption(mHttpOption)
                    ->build();
        
        mHttpServer->start();
        return 0;
    }

    return -AlreadyExists;
}

int _WebSocketServer::close() {
    if(mSocketMonitor != nullptr) {
        mSocketMonitor->close();
        mSocketMonitor = nullptr;
    }

    if(mHttpServer != nullptr) {
        mHttpServer->close();
        mHttpServer = nullptr;
    }
    
    return 0;
}

void _WebSocketServer::onSocketMessage(int event,Socket s,ByteArray pack) {
    WebSocketLinker client = mLinkerManager->getLinker(s);

    WebSocketListener listener = client->getWebSocketListener();
    if(listener == nullptr) {
        LOG(ERROR)<<"WebSocket listener is null!!!";
        return;
    }

    switch(event) {
        case SocketEvent::Message: {
            WebSocketParser parser = client->getParser();

            parser->pushParseData(pack);
            ArrayList<WebSocketFrame> lists = parser->doParse();

            lists->foreach([this,&client,&listener](WebSocketFrame &frame) {
                int opcode = frame->getHeader()->getOpCode();
                switch(opcode) {
                    case st(WebSocketProtocol)::OPCODE_CONTROL_PING: {
                        String pingmessage = frame->getData()->toString();
                        if (listener->onPing(pingmessage,client) == PingResultResponse) {
                            client->sendPongMessage(frame->getData());
                        }
                    }
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:{
                        listener->onPong(frame->getData()->toString(),client);
                    }
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE: {
                        mSocketMonitor->remove(client->getSocket());
                        client->getSocket()->close();
                        mLinkerManager->removeLinker(client);
                        listener->onDisconnect(client);
                    }
                    break;

                    default:
                        listener->onData(frame,client);
                }
                return Global::Continue;
            });
        }
        break;

        case SocketEvent::Connect:
        //TODO
        break;

        case SocketEvent::Disconnect: {
            if(client != nullptr) {
                mLinkerManager->removeLinker(client);
                listener->onDisconnect(client);
            } else {
                LOG(ERROR)<<"client is already remove!!!";
            }
        }
        break;
    }
}

void _WebSocketServer::onHttpMessage(int event,sp<_HttpLinker> client,sp<_HttpResponseWriter> w,HttpPacket request) {
    switch(event) {
        case HttpEvent::Message: {
            HttpHeader header = request->getHeader();
            String path = header->getUrl()->getPath();

            WebSocketListener listener = mWsListeners->get(path);
            
            if(listener == nullptr || path == nullptr) {
                LOG(ERROR)<<"Unwanted websocket connection";
                client->close();
                return;
            }
            
            String upgrade = header->getValue(st(HttpHeader)::Upgrade);
            String key = header->getValue(st(HttpHeader)::SecWebSocketKey);
            String version = header->getValue(st(HttpHeader)::SecWebSocketVersion);

            if (upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
                // remove fd from http epoll
                mHttpServer->deMonitor(client->getSocket());

                while(mLinkerManager->getLinker(client->getSocket())!= nullptr) {
                    LOG(INFO)<<"websocket client is not removed";
                    usleep(1000*5);
                }
                
                WebSocketLinker wsClient = mLinkerManager->addLinker(client->getSocket(),
                                                                    version->toBasicInt());

                wsClient->setProtocols(header->getValue(st(HttpHeader)::SecWebSocketProtocol));
                wsClient->setWebSocketKey(header->getValue(st(HttpHeader)::SecWebSocketKey));
                WebSocketParser parser = wsClient->getParser();

                if (!parser->validateHandShake(header)) {
                    return;
                }

                // Try to check whether extension support deflate.
                WebSocketPermessageDeflate deflate = parser->validateExtensions(header);
                if (deflate != nullptr) {
                    wsClient->setDeflater(deflate);
                }
                ArrayList<String> protocols = parser->extractSubprotocols(header);
                if (protocols != nullptr && protocols->size() != 0) {
                    LOG(ERROR)<<"Websocket Server Protocol is not null";
                } else {
                    //TODO
                }
                
                mSocketMonitor->bind(client->getSocket(),AutoClone<SocketListener>(this));
                //mWsListener->onConnect(wsClient);
                listener->onConnect(wsClient);
                wsClient->setWebSocketListener(listener);
                wsClient->setPath(path);

                WebSocketComposer composer = wsClient->getComposer();
                //String p = wsClient->getHttpHeader()->getValue(st(HttpHeader)::SecWebSocketProtocol);
                //String k = wsClient->getHttpHeader()->getValue(st(HttpHeader)::SecWebSocketKey);
                String p = wsClient->getProtocols();
                String k = wsClient->getWebSocketKey();
                HttpResponse shakeresponse = composer->genServerShakeHandMessage(k,p);

                HttpResponseWriter writer = createHttpResponseWriter(client->getSocket()->getOutputStream());
                //long ret = client->getSocket()->getOutputStream()->write(shakeresponse);
                if(writer->write(shakeresponse) < 0) {
                    LOG(ERROR)<<"Websocket Server send response fail,reason:"<<strerror(errno);
                }
            }
        }
        
        break;

        case HttpEvent::Connect:
        case HttpEvent::Disconnect:
        break;
    }
}

}  // namespace obotcha
