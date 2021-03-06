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

namespace obotcha {

//-----WebSocketServer-----
_WebSocketServer::_WebSocketServer() {
    int threadnum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
    mSocketMonitor = createSocketMonitor(threadnum);
    mSendTimeout = -1;
    mRcvTimeout = -1;
}

void _WebSocketServer::setSendTimeout(long timeout) {
    mSendTimeout = timeout;
}

long _WebSocketServer::getSendTimeout() {
    return mSendTimeout;
}

void _WebSocketServer::setRcvTimeout(long timeout) {
    mRcvTimeout = timeout;
}

long _WebSocketServer::getRcvTimeout() {
    return mRcvTimeout;
}

int _WebSocketServer::bind(InetAddress addr, String path,
                           WebSocketListener listener) {
    if (mHttpServer != nullptr) {
      return -AlreadyExists;
    }

    mAddress = addr;
    mWsListener = listener;
    
    mHttpServer = createHttpServerBuilder()
                ->setAddress(addr)
                ->setListener(AutoClone(this))
                ->build();

    mHttpServer->setSendTimeout(mSendTimeout);
    mHttpServer->setRcvTimeout(mRcvTimeout);
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
        case st(Socket)::Message: {
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

                parser->setParseData(pack);
                WebSocketHeader header = parser->parseHeader();

                int opcode = header->getOpCode();
                int framesize = header->getFrameLength();
                int headersize = header->getHeadSize();

                if (opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
                    ByteArray msgData = parser->parseContent(true);
                    String msg = msgData->toString();
                    WebSocketFrame frame = createWebSocketFrame(header,msg);
                    mWsListener->onMessage(client, frame);
                } else if (opcode == st(WebSocketProtocol)::OPCODE_BINARY) {
                    if (header->isFinalFrame()) {
                        ByteArray msgData = parser->parseContent(true);
                        WebSocketFrame frame = createWebSocketFrame(header,msgData);
                        mWsListener->onData(client, msgData);
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

        case st(Socket)::Connect:
        //TODO
        break;

        case st(Socket)::Disconnect: {
            st(WebSocketClientManager)::getInstance()->removeClient(client);
            mWsListener->onDisconnect(client);
        }
        break;
    }
}

void _WebSocketServer::onHttpMessage(int event,sp<_HttpClientInfo> client,sp<_HttpResponseWriter> w,HttpPacket request) {
    switch(event) {
        case st(HttpListener)::Message: {
            HttpHeader header = request->getHeader();
            String upgrade = header->getValue(st(HttpHeader)::Upgrade);
            String key = header->getValue(st(HttpHeader)::SecWebSocketKey);
            String version = header->getValue(st(HttpHeader)::SecWebSocketVersion);
            if (upgrade != nullptr && upgrade->equalsIgnoreCase("websocket")) {
                // remove fd from http epoll
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

                mSocketMonitor->bind(client->getSocket(),AutoClone(this));
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

        case st(HttpListener)::Connect:
        case st(HttpListener)::Disconnect:
        break;
    }
}

}  // namespace obotcha
