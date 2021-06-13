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
_WebSocketServer::_WebSocketServer() {
    int threadnum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
    mSocketMonitor = createSocketMonitor(threadnum);
    mPath = nullptr;
    mAddress = nullptr;
    mHttpServer = nullptr;
    //mWsListener = nullptr;
    mWsOption = nullptr;
    mHttpOption = nullptr;
    mListenersLock = createMutex();
    mWsListeners = createHashMap<String,WebSocketListener>();
}

int _WebSocketServer::bind(InetAddress addr, String path,
                           WebSocketListener listener,WebSocketOption wsoption,HttpOption httpoption) {
    if (mHttpServer != nullptr) {
      return -AlreadyExists;
    }
    mPath = path;
    mAddress = addr;
    //wangsl
    //mWsListener = listener;
    mWsListeners->put(mPath,listener);
    //wangsl
    mWsOption = wsoption;
    mHttpOption = httpoption;
    
    if(mHttpServer == nullptr) {
        mHttpServer = createHttpServerBuilder()
                    ->setAddress(addr)
                    ->setListener(AutoClone(this))
                    ->setOption(mHttpOption)
                    ->build();
        
        mHttpServer->start();
    }

    return 0;
}

int _WebSocketServer::start() {
    return 0;
}

int _WebSocketServer::close() {
    mSocketMonitor->close();
    mHttpServer->close();
    
    return 0;
}

void _WebSocketServer::onSocketMessage(int event,Socket s,ByteArray pack) {
    //int fd = s->getFd();
    WebSocketLinker client =
        st(WebSocketLinkerManager)::getInstance()->getLinker(s);

    WebSocketListener listener = client->getWebSocketListener();
    if(listener == nullptr) {
        LOG(ERROR)<<"WebSocket listener is null!!!";
        return;
    }

    switch(event) {
        case SocketEvent::Message: {
            bool isRmClient = false;
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
                        st(WebSocketLinkerManager)::getInstance()->removeLinker(client);
                        listener->onDisconnect(client);
                    }
                    break;

                    default:
                        listener->onData(frame,client);
                }
                return 1;
            });
        }
        break;

        case SocketEvent::Connect:
        //TODO
        break;

        case SocketEvent::Disconnect: {
            if(client != nullptr) {
                st(WebSocketLinkerManager)::getInstance()->removeLinker(client);
                listener->onDisconnect(client);
            } else {
                printf("client is already remove!!! \n");
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

            WebSocketListener listener = nullptr;
            {
                AutoLock l(mListenersLock);
                listener = mWsListeners->get(path);
            }
            
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

                while(st(WebSocketLinkerManager)::getInstance()->getLinker(client->getSocket())!= nullptr) {
                    LOG(INFO)<<"websocket client is not removed";
                    usleep(1000*5);
                }
                
                WebSocketLinker wsClient = st(WebSocketLinkerManager)::getInstance()->addLinker(client->getSocket(),
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
                wsClient->setWebSocketListener(listener);

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
