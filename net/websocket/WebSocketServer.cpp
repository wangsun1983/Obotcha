#include "WebSocketServer.hpp"

#include <stdio.h>
#include <sys/epoll.h>

#include "Error.hpp"
#include "WebSocketProtocol.hpp"
#include "HttpClientInfo.hpp"
#include "WebSocketClientManager.hpp"
#include "WebSocketComposer.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"
#include "HttpServerBuilder.hpp"
#include "Inet4Address.hpp"
#include "HttpOption.hpp"

namespace obotcha {

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer() {
    int threadnum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
    mSocketMonitor = createSocketMonitor(threadnum);
}

int _WebSocketServer::bind(InetAddress addr, String path,
                           WebSocketListener listener,WebSocketOption option) {
    if (mHttpServer != nullptr) {
      return -AlreadyExists;
    }

    mAddress = addr;
    mWsListener = listener;
    
    HttpOption httpoption = nullptr;

    if(option != nullptr) {
        httpoption = createHttpOption();
        httpoption->setSendTimeout(option->getSendTimeout());
        httpoption->setRecvTimeout(option->getRcvTimeout());
    }
    mHttpServer = createHttpServerBuilder()
                ->setAddress(addr)
                ->setListener(AutoClone(this))
                ->setOption(httpoption)
                ->build();
    
    mHttpServer->start();

    return 0;
}

int _WebSocketServer::start() {
    return 0;
}

int _WebSocketServer::release() {
    mSocketMonitor->release();
    mHttpServer->exit();
    
    return 0;
}

void _WebSocketServer::onSocketMessage(int event,Socket s,ByteArray pack) {
    int fd = s->getFd();
    WebSocketClientInfo client =
        st(WebSocketClientManager)::getInstance()->getClient(s);
    switch(event) {
        case SocketEvent::Message: {
            bool isRmClient = false;
            WebSocketParser parser = client->getParser();
            WebSocketBuffer defferedBuff = client->getDefferedBuffer();
            if (defferedBuff != nullptr) {
                if(defferedBuff->mBuffer != nullptr) {
                    defferedBuff->mBuffer->append(pack);
                } else {
                    defferedBuff->mBuffer = pack;
                }
                pack = defferedBuff->mBuffer;
            }
            printf("_WebSocketServer onSocketMessage trace2 \n");
            while (1) {
                int readIndex = 0;
                if (!parser->validateEntirePacket(pack)) {
                    // it is not a full packet
                    if (defferedBuff == nullptr) {
                        defferedBuff = createWebSocketBuffer();
                        defferedBuff->mBuffer = pack;
                        st(WebSocketClientManager)::getInstance()->getClient(s)->setDefferedBuffer(defferedBuff);
                    }
                    break;
                }
                printf("_WebSocketServer onSocketMessage trace3 \n");
                parser->setParseData(pack);
                WebSocketHeader header = parser->parseHeader();

                int opcode = header->getOpCode();
                int framesize = header->getFrameLength();
                int headersize = header->getHeadSize();
                printf("_WebSocketServer onSocketMessage onMessage trace1,opcode is %d\n",opcode);

                if (opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
                    printf("_WebSocketServer onSocketMessage onMessage trace2\n");
                    ByteArray msgData = parser->parseContent(true);
                    String msg = msgData->toString();
                    WebSocketFrame frame = createWebSocketFrame(header,msg);
                    mWsListener->onMessage(client, frame);
                } else if (opcode == st(WebSocketProtocol)::OPCODE_BINARY) {
                    if (header->isFinalFrame()) {
                        ByteArray msgData = parser->parseContent(true);
                        WebSocketFrame frame = createWebSocketFrame(header,msgData);
                        mWsListener->onData(client, frame);
                    } else {
                        ByteArray msgData = parser->parseContent(false);
                        WebSocketBuffer buff = createWebSocketBuffer();
                        buff->mBuffer = msgData;
                        client->setContinueBuffer(buff);
                    }
                } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
                    ByteArray buff = parser->parsePingBuff();
                    if (mWsListener->onPing(client, buff->toString()) == PingResultResponse) {
                        ByteArray resp = client->getComposer()->genPongMessage(client,buff->toString());
                        send(fd,resp->toValue(),resp->size(),0);
                    }
                } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
                    ByteArray pong = parser->parsePongBuff();
                    String msg = pong->toString();
                    mWsListener->onPong(client, msg);
                } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
                    isRmClient = true;
                    break;
                } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
                    ByteArray msgData = parser->parseContent(false);
                    WebSocketBuffer continuebuff = client->getContinueBuffer();
                    continuebuff->mBuffer->append(msgData);

                    if (header->isFinalFrame()) {
                        ByteArray out = parser->validateContinuationContent(
                            client->getContinueBuffer()->mBuffer);
                        WebSocketFrame frame = createWebSocketFrame(header,out);
                        mWsListener->onData(client, frame);
                        continuebuff->mBuffer = nullptr;
                    }
                }

                // check whether there are two ws messages received in one buffer!
                // len -= (framesize + headersize);
                int resetLength = (pack->size() - (framesize + headersize));
                readIndex += (framesize + headersize);
                
                if (resetLength > 0) {
                    byte *pdata = pack->toValue();
                    pack = createByteArray(&pdata[readIndex], resetLength);
                    continue;
                }

                client->setDefferedBuffer(nullptr);
                break;
            }

            if(isRmClient) {
                st(WebSocketClientManager)::getInstance()->removeClient(client);
                mWsListener->onDisconnect(client);
            }
        }
        break;

        case SocketEvent::Connect:
        //TODO
        break;

        case SocketEvent::Disconnect: {
            if(client != nullptr) {
                printf("websocket onsocket disconnect,fd is %d \n",client->getSocket()->getFd());
                st(WebSocketClientManager)::getInstance()->removeClient(client);
                mWsListener->onDisconnect(client);
            } else {
                printf("client is already remove!!! \n");
            }
        }
        break;
    }
}

void _WebSocketServer::onHttpMessage(int event,sp<_HttpClientInfo> client,sp<_HttpResponseWriter> w,HttpPacket request) {
    switch(event) {
        case HttpEvent::Message: {
            HttpHeader header = request->getHeader();
            String upgrade = header->getValue(st(HttpHeader)::Upgrade);
            String key = header->getValue(st(HttpHeader)::SecWebSocketKey);
            String version = header->getValue(st(HttpHeader)::SecWebSocketVersion);
            if (upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
                // remove fd from http epoll
                printf("deMonitor \n");
                mHttpServer->deMonitor(client->getSocket());

                while(st(WebSocketClientManager)::getInstance()->getClient(client->getSocket())!= nullptr) {
                    LOG(INFO)<<"websocket client is not removed";
                    usleep(1000*5);
                }
                
                WebSocketClientInfo wsClient = st(WebSocketClientManager)::getInstance()->addClient(client->getSocket(),
                                                                    version->toBasicInt());
                wsClient->setHttpHeader(header);
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
                printf("move to socket monitor \n");
                mSocketMonitor->bind(client->getSocket(),AutoClone<SocketListener>(this));
                mWsListener->onConnect(wsClient);

                WebSocketComposer composer = wsClient->getComposer();
                ByteArray shakeresponse = composer->genShakeHandMessage(wsClient);
                long ret = client->getSocket()->getOutputStream()->write(shakeresponse);
                if(ret < 0) {
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
