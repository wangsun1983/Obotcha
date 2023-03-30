#include "WebSocketServer.hpp"
#include "WebSocketProtocol.hpp"
#include "HttpLinker.hpp"
#include "WebSocketComposer.hpp"
#include "Log.hpp"
#include "HttpServerBuilder.hpp"
#include "HttpOption.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "NetEvent.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketValidator.hpp"
#include "Inspect.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer(InetAddress address,HttpOption option,int threadnum) {
    mHttpServer = nullptr;
    mWsListeners = createConcurrentHashMap<String,WebSocketListener>();
    mLinkers = createConcurrentHashMap<Socket,sp<_WebSocketLinker>>();
    mThreadNum = threadnum;
    mHttpOption = option;
    mAddress = address;
    mStatus = Idle;
}

int _WebSocketServer::bind(String path,WebSocketListener l) {
    if(mWsListeners->get(path) != nullptr) {
        LOG(ERROR)<<"websocket server path:"<<path->toChars()<<",already registed!!!";
        return -1;
    }

    mWsListeners->put(path,l);
    return 0;
}

int _WebSocketServer::start() {
    Inspect(mStatus != Idle,-1);

    mStatus = Running;
    mSocketMonitor = createSocketMonitor(mThreadNum);
    mHttpServer = createHttpServerBuilder()
                    ->setAddress(mAddress)
                    ->setListener(AutoClone(this))
                    ->setOption(mHttpOption)
                    ->build();

    return mHttpServer->start();
}

int _WebSocketServer::close() {
    Inspect(mStatus != Running,-1);
    mStatus = Closed;

    mSocketMonitor->close();
    mHttpServer->close();
    
    //close all client connection
    ForEveryOne(pair,mLinkers) {
        auto client = pair->getKey();
        client->close();
    }
    
    mSocketMonitor = nullptr;
    mHttpServer = nullptr;
    return 0;
}

void _WebSocketServer::dump() {
    //mSocketMonitor->dump();
}

void _WebSocketServer::onSocketMessage(int event,Socket sock,ByteArray pack) {
    WebSocketLinker client = mLinkers->get(sock);
    WebSocketListener listener = client->getWebSocketListener();
    if(listener == nullptr) {
        LOG(ERROR)<<"WebSocket listener is null!!!";
        return;
    }

    switch(event) {
        case st(NetEvent)::Message: {
            WebSocketInputReader reader = client->getInputReader();
            reader->push(pack);
            ArrayList<WebSocketFrame> lists;
            try {
                lists = reader->pull();
            } catch(...) {
                //this client's data is illegal
                mLinkers->remove(sock);
                listener->onDisconnect(client); //TODO
                sock->close();
                return;
            }
            ForEveryOne(frame,lists) {
                int opcode = frame->getHeader()->getOpCode();
                switch(opcode) {
                    case st(WebSocketProtocol)::OPCODE_CONTROL_PING: {
                        if (listener->onPing(frame->getData()->toString(),client) 
                                == st(WebSocketListener)::AutoResponse) {
                            client->sendPongMessage(frame->getData());
                        }
                    }
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:{
                        listener->onPong(frame->getData()->toString(),client);
                    }
                    break;

                    case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE: {
                        //TODO? save WebSocketFrame to transport to user???
                        client->sendCloseMessage();
                    }
                    break;

                    default:
                        //python client will send a null data when finish sending file.
                        //add a null data check
                        if(frame->getData() != nullptr) {
                            listener->onData(frame,client);
                        }
                }
            }
        }
        break;

        case st(NetEvent)::Connect:
            //nothing,connect info is send to client by onHttpMessage
        break;

        case st(NetEvent)::Disconnect: {
            if(client != nullptr) {
                mLinkers->remove(sock);
                listener->onDisconnect(client);
            } else {
                LOG(ERROR)<<"client is already remove!!!";
            }
        }
        break;
    }
}

void _WebSocketServer::onHttpMessage(int event,HttpLinker client,HttpResponseWriter w,HttpPacket request) {
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
            
            auto upgrade = header->getUpgrade();

            if (upgrade != nullptr && upgrade->get()->equalsIgnoreCase("websocket")) {
                String key = header->getWebSocketKey()->get();
                int version = header->getWebSocketVersion()->get();
    
                mHttpServer->remove(client);
                while(mLinkers->get((client->mSocket))!= nullptr) {
                    LOG(INFO)<<"Websocket client is not removed";
                    usleep(1000*5);
                }
                
                WebSocketLinker wsClient = createLinker(client,version);
                if(header->getWebSocketProtocol() != nullptr) {
                    wsClient->setProtocols(header->getWebSocketProtocol()->get());
                }

                wsClient->setWebSocketKey(key);
                auto inspector = wsClient->getInspector();
                if (!inspector->validateHandShake(header)) {
                    LOG(INFO)<<"websocket client header is invalid";
                    return;
                }

                mLinkers->put(wsClient->getSocket(),wsClient);
                // Try to check whether extension support deflate.
                WebSocketPermessageDeflate deflate = inspector->validateExtensions(header);
                if (deflate != nullptr) {
                    wsClient->setDeflater(deflate);
                }
                
                ArrayList<String> subProtocols = inspector->extractSubprotocols(header);
                if (subProtocols != nullptr && subProtocols->size() != 0) {
                    LOG(ERROR)<<"Websocket Server Protocol is not null";
                } else {
                    //TODO
                }
                
                listener->onConnect(wsClient);
                
                wsClient->setWebSocketListener(listener);
                wsClient->setPath(path);
                mSocketMonitor->bind(client->mSocket,AutoClone<SocketListener>(this));
                HttpResponse shakeresponse = inspector->createServerShakeHandMessage(key,
                                                                                     wsClient->getProtocols(),
                                                                                     deflate);
                if(client->getWriter()->write(shakeresponse) < 0) {
                    LOG(ERROR)<<"Websocket Server send response fail,reason:"<<strerror(errno);
                    client->close();
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

WebSocketLinker _WebSocketServer::createLinker(sp<_HttpLinker> linker,int version) {
    return createWebSocketLinker(version,linker->mSocket);;
}

}  // namespace obotcha
