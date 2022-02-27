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
#include "HttpPacketWriterImpl.hpp"
#include "NetEvent.hpp"

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

void _WebSocketServer::dump() {
    mSocketMonitor->dump();
}

void _WebSocketServer::onSocketMessage(int event,Socket s,ByteArray pack) {
    WebSocketLinker client = mLinkerManager->get(s);

    WebSocketListener listener = client->getWebSocketListener();
    if(listener == nullptr) {
        LOG(ERROR)<<"WebSocket listener is null!!!";
        return;
    }

    switch(event) {
        case st(NetEvent)::Message: {
            WebSocketParser parser = client->getParser();

            parser->pushParseData(pack);
            ArrayList<WebSocketFrame> lists = parser->doParse();
            auto iterator = lists->getIterator();
            while(iterator->hasValue()) {
                WebSocketFrame frame = iterator->getValue();
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
                        //do not do any operation until client close!!!.
                        //if server close directly,server will wait for 
                        //shakehands....
                        ByteArray data = createString("end")->toByteArray();
                        client->sendCloseMessage(data);
                    }
                    break;

                    default:
                        //python client will send a null data when finish sending file.
                        //add a null data check
                        if(frame->getData() != nullptr) {
                            listener->onData(frame,client);
                        }
                }
                iterator->next();
            }
        }
        break;

        case st(NetEvent)::Connect:
            //nothing,connect info is send to client by onHttpMessage
        break;

        case st(NetEvent)::Disconnect: {
            if(client != nullptr) {
                //LOG(ERROR)<<"client is removed by socket callback";
                mLinkerManager->remove(client);
                listener->onDisconnect(client);
            } else {
                LOG(ERROR)<<"client is already remove!!!";
            }
        }
        break;
    }
}

void _WebSocketServer::onHttpMessage(int event,sp<_HttpLinker> client,HttpResponseWriter w,HttpPacket request) {
    switch(event) {
        case st(NetEvent)::Message: {
            HttpHeader header = request->getHeader();
            String path = header->getUrl()->getPath();

            WebSocketListener listener = mWsListeners->get(path);
            
            if(listener == nullptr || path == nullptr) {
                LOG(ERROR)<<"Unwanted websocket connection";
                client->close();
                return;
            }
            
            //String upgrade = header->get(st(HttpHeader)::Upgrade);
            auto httpUpgrade = header->getUpgrade();
            //String key = header->get(st(HttpHeader)::SecWebSocketKey);
            String key = header->getWebSocketKey()->get();

            //String version = header->get(st(HttpHeader)::SecWebSocketVersion);
            int version = header->getWebSocketVersion()->get();

            if (httpUpgrade != nullptr && httpUpgrade->get()->equalsIgnoreCase("websocket")) {
                // remove fd from http epoll
                //mHttpServer->deMonitor(client->getSocket());
                mHttpServer->remove(client);

                while(mLinkerManager->get((client->mSocket))!= nullptr) {
                    LOG(INFO)<<"websocket client is not removed";
                    usleep(1000*5);
                }
                
                WebSocketLinker wsClient = mLinkerManager->add(client->mSocket,version);

                //wsClient->setProtocols(header->get(st(HttpHeader)::SecWebSocketProtocol));
                //wsClient->setWebSocketKey(header->get(st(HttpHeader)::SecWebSocketKey));
                if(header->getWebSocketProtocol() != nullptr) {
                    wsClient->setProtocols(header->getWebSocketProtocol()->get());
                }
                wsClient->setWebSocketKey(header->getWebSocketKey()->get());

                WebSocketParser parser = wsClient->getParser();

                if (!parser->validateHandShake(header)) {
                    LOG(INFO)<<"websocket client header is invalid";
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
                
                //mWsListener->onConnect(wsClient);
                listener->onConnect(wsClient);
                wsClient->setWebSocketListener(listener);
                wsClient->setPath(path);
                mSocketMonitor->bind(client->mSocket,AutoClone<SocketListener>(this));
                
                WebSocketComposer composer = wsClient->getComposer();
                //String p = wsClient->getHttpHeader()->getValue(st(HttpHeader)::SecWebSocketProtocol);
                //String k = wsClient->getHttpHeader()->getValue(st(HttpHeader)::SecWebSocketKey);
                ArrayList<String> p = wsClient->getProtocols();
                String k = wsClient->getWebSocketKey();
                HttpResponse shakeresponse = composer->genServerShakeHandMessage(k,p);

                HttpPacketWriter writer = client->getWriter();//createHttpPacketWriterImpl(client->mSocket->getOutputStream());
                //long ret = client->getSocket()->getOutputStream()->write(shakeresponse);
                if(writer->write(shakeresponse) < 0) {
                    LOG(ERROR)<<"Websocket Server send response fail,reason:"<<strerror(errno);
                }
            } else {
                LOG(ERROR)<<"Websocket Server recv invalid";
            }
        }
        
        break;

        case st(NetEvent)::Connect:
        break;

        case st(NetEvent)::Disconnect:
        break;
    }
}

}  // namespace obotcha
