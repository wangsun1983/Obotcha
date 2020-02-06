#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketProtocol.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpUrl.hpp"
#include "HttpUrlParser.hpp"
#include "HttpPacket.hpp"
#include "Random.hpp"
#include "Base64.hpp"

namespace obotcha {

_WebSocketHybi13Composer::_WebSocketHybi13Composer(int type,int maxFrameSize):_WebSocketComposer(type,maxFrameSize){
    mSha = createSha(SHA_1);
    mBase64 = createBase64();
    mRand = createRandom();
}

ByteArray _WebSocketHybi13Composer::genShakeHandMessage(WebSocketClientInfo h) {
    printf("mType is %d \n",mType);
    switch(mType) {
        case WsClientComposer:
        return _genClientShakeHandMessage(h);

        case WsServerComposer:
        return _genServerShakeHandMessage(h);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::_genClientShakeHandMessage(WebSocketClientInfo client) {
    printf("genClientShakeHandMessage trace1\n");
    HttpUrl httpUrl = st(HttpUrlParser)::parseUrl(client->getConnectUrl());
    HttpPacket packet = createHttpPacket();
    packet->setMethod(st(HttpMethod)::Get);
    packet->setHeader(client->getHttpHeader());
    packet->setUrl(httpUrl->getPath());
    packet->setMajorVersion(1);
    packet->setMinorVersion(1);

    String host = httpUrl->getHost()->append(":")->append(createString(httpUrl->getPort()));
    packet->getHeader()->setValue(st(HttpHeader)::Host,host);
    packet->getHeader()->setValue(st(HttpHeader)::SecWebSocketVersion,"13");
    if(packet->getHeader()->getValue(st(HttpHeader)::Accept) == nullptr) {
        packet->getHeader()->setValue(st(HttpHeader)::Accept,"*/*");
    }

    if(packet->getHeader()->getValue(st(HttpHeader)::AcceptLanguage) == nullptr) {
        packet->getHeader()->setValue(st(HttpHeader)::AcceptLanguage,"en-US,en;q=0.5");
    }

    if(packet->getHeader()->getValue(st(HttpHeader)::AcceptEncoding) == nullptr) {
        packet->getHeader()->setValue(st(HttpHeader)::AcceptEncoding,"gzip, deflate");
    }

    if(packet->getHeader()->getValue(st(HttpHeader)::Origin) == nullptr) {
        packet->getHeader()->setValue(st(HttpHeader)::Origin,"null");
    }

    if(packet->getHeader()->getValue(st(HttpHeader)::SecWebSocketKey) == nullptr) {
        //we should gen a sec key
        Random rand = createRandom();
        int v = rand->nextInt();
        Base64 base64key = createBase64();
        String key = base64key->decode(createString(v));
        printf("sec websocket key is %s \n",key->toChars());
        packet->getHeader()->setValue(st(HttpHeader)::SecWebSocketKey,key);
    }

    if(packet->getHeader()->getValue(st(HttpHeader)::Connection) == nullptr) {
        packet->getHeader()->setValue(st(HttpHeader)::Connection,"keep-alive, Upgrade");
    }

    if(packet->getHeader()->getValue(st(HttpHeader)::Upgrade) == nullptr) {
        packet->getHeader()->setValue(st(HttpHeader)::Upgrade,"websocket");
    }

    if(packet->getHeader()->getValue(st(HttpHeader)::Pragma) == nullptr) {
        packet->getHeader()->setValue(st(HttpHeader)::Pragma,"no-cache");
    }

    if(packet->getHeader()->getValue(st(HttpHeader)::CacheControl) == nullptr) {
        packet->getHeader()->setValue(st(HttpHeader)::CacheControl,"no-cache");
    }
    printf("genClientShakeHandMessage trace2\n");
    
    return createByteArray(packet->genHttpRequest());
}

ByteArray _WebSocketHybi13Composer::_genServerShakeHandMessage(WebSocketClientInfo  info) {
    HttpHeader h = info->getHttpHeader();
    String key = h->getValue(st(HttpHeader)::SecWebSocketKey);

    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    ByteArray sha1_content = mSha->encryptRawData(createByteArray(key_mgic));
    String base64 = mBase64->encode(sha1_content)->toString();
    
    String head = "HTTP/1.1 101 Switching Protocols\r\n";
    String upgrade = head->append("Upgrade: websocket\r\n");
    String connection = upgrade->append("Connection: Upgrade\r\n");

    String protocols = h->getValue(st(HttpHeader)::SecWebSocketProtocol);
    if(protocols != nullptr) {
        //TODO
        connection = connection->append("Sec-WebSocket-Protocol:")->append(protocols)->append("\r\n");
    }

    String resp = connection->append("Sec-WebSocket-Accept:")->append(base64)->append("\r\n");

    //check whetehr we have Deflate
    printf("genServerShakeHandeMessage trace1 \n");
    
    WebSocketPermessageDeflate deflater = info->getDeflater();
    if(deflater != nullptr) {
        printf("genServerShakeHandeMessage trace2 \n");
        resp = resp->append("Sec-WebSocket-Extensions:")
                   ->append("permessage-deflate")
                   ->append(";client_max_window_bits=")
                   ->append(createString(deflater->getServerMaxWindowBits()))
                   ->append("\r\n");
    }

    resp->append("\r\n");

    return createByteArray(resp);
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genTextMessage(WebSocketClientInfo info,String content) {
    switch(mType) {
        case WsClientComposer:
        //return genClientTextMessage(info,content);
        return _genClientMessage(info,createByteArray(content),st(WebSocketProtocol)::OPCODE_TEXT);

        case WsServerComposer:
        return _genServerMessage(info,createByteArray(content),st(WebSocketProtocol)::OPCODE_TEXT);
    }

    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::_genClientMessage(WebSocketClientInfo info,ByteArray content,int type) {
    ArrayList<ByteArray> genResult = createArrayList<ByteArray>();

    ByteArray entireMessage = nullptr;
    WebSocketPermessageDeflate deflater = info->getDeflater();

    if(deflater != nullptr) {
        entireMessage = deflater->compress(content);
    } else {
        entireMessage = content;
    }

    const byte *pData = entireMessage->toValue();
    int index = 0;
    bool isFirstFrame = true;
    bool isLastFrame = false;
    while(1) {
        int len = (entireMessage->size()-index) > mMaxFrameSize?mMaxFrameSize:(entireMessage->size() - index);
        printf("index is %d,len is %d \n",index,len);
        ByteArray message = createByteArray(pData + index,len);
        index += len;
        if(index == entireMessage->size()) {
            isLastFrame = true;
        }

        ByteArray sink = createByteArray(message->size() + 64);
        ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

        int b0 = 0;//formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
        if(isFirstFrame) {
            b0 = type;
            isFirstFrame = false;
        } else {
            b0 = st(WebSocketProtocol)::OPCODE_CONTINUATION;
        }

        if(isLastFrame) {
            b0 |= st(WebSocketProtocol)::B0_FLAG_FIN;
        }

        printf("b0 is %x \n",b0);
        sinkWriter->writeByte(b0);
        
        ByteArray maskKey = createByteArray(4);
        int b1 = 0;

        if(info->getWebSocketHeader()->getMasked()) {
            b1 = st(WebSocketProtocol)::B1_FLAG_MASK;
            //random.nextBytes(maskKey);
            mRand->nextBytes(maskKey);
        }
    
        int byteCount = message->size();
        printf("byteCount is %d\n",byteCount);
        if (byteCount <= st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
            b1 |= (int) byteCount;
            sinkWriter->writeByte(b1);
        } else if (byteCount <= st(WebSocketProtocol)::PAYLOAD_SHORT_MAX) {
            b1 |= st(WebSocketProtocol)::PAYLOAD_SHORT;
            sinkWriter->writeByte(b1);
            sinkWriter->writeShort((int) byteCount);
        } else {
            b1 |= st(WebSocketProtocol)::PAYLOAD_LONG;
            sinkWriter->writeByte(b1);
            sinkWriter->writeLong(byteCount);
        }

        if(info->getWebSocketHeader()->getMasked()) {
            sinkWriter->writeByteArray(maskKey);
            //writeMaskedSynchronized(buffer, byteCount);
            ByteArray maskBuff = createByteArray(message);
            printf("start toggleMask,maskBuff size is %d,message size is %d \n",maskBuff->size(),message->size());
            st(WebSocketProtocol)::toggleMask(maskBuff,maskKey);
            sinkWriter->writeByteArray(maskBuff);
        } else {
            sinkWriter->writeByteArray(message);
        }
        
        sink->qucikShrink(sinkWriter->getIndex());

        genResult->add(sink);

        if(isLastFrame) {
            break;
        }
    }

    return genResult;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::_genServerMessage(WebSocketClientInfo info,ByteArray content,int type) {
    ArrayList<ByteArray> genResult = createArrayList<ByteArray>();

    ByteArray entireMessage = content;

    const byte *pData = entireMessage->toValue();
    int index = 0;
    bool isFirstFrame = true;
    bool isLastFrame = false;
    while(1) {
        int len = (entireMessage->size()-index) > mMaxFrameSize?mMaxFrameSize:(entireMessage->size() - index);
        printf("index is %d,len is %d \n",index,len);
        ByteArray message = createByteArray(pData + index,len);
        index += len;
        if(index == entireMessage->size()) {
            isLastFrame = true;
        }

        ByteArray sink = createByteArray(message->size() + 64);
        ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

        int b0 = 0;//formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
        if(isFirstFrame) {
            b0 = type;
            isFirstFrame = false;
        } else {
            b0 = st(WebSocketProtocol)::OPCODE_CONTINUATION;
        }

        if(isLastFrame) {
            b0 |= st(WebSocketProtocol)::B0_FLAG_FIN;
        }

        printf("b0 is %x \n",b0);
        sinkWriter->writeByte(b0);

        int b1 = message->size();
        printf("byteCount is %d\n",b1);
        if (b1 <= st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
            sinkWriter->writeByte(b1);
        } else if (b1 <= st(WebSocketProtocol)::PAYLOAD_SHORT_MAX) {
            sinkWriter->writeByte(st(WebSocketProtocol)::PAYLOAD_SHORT);
            sinkWriter->writeShort(b1);
        } else {
            sinkWriter->writeByte(st(WebSocketProtocol)::PAYLOAD_BYTE_MAX);
            sinkWriter->writeLong(b1);
        }

        sinkWriter->writeByteArray(message);
        sink->qucikShrink(sinkWriter->getIndex());

        genResult->add(sink);

        if(isLastFrame) {
            break;
        }
    }

    return genResult;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genBinaryMessage(WebSocketClientInfo info,ByteArray content) {
    switch(mType) {
        case WsClientComposer:
        return _genClientMessage(info,content,st(WebSocketProtocol)::OPCODE_BINARY);

        case WsServerComposer:
        return _genServerMessage(info,content,st(WebSocketProtocol)::OPCODE_BINARY);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genPingMessage(WebSocketClientInfo info ,String msg) {
    switch(mType) {
        case WsClientComposer:
        return _genClientControlMessage(info,
                                        createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PING);

        case WsServerComposer:
        return _genServerControlMessage(info,
                                        createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PING);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genPongMessage(WebSocketClientInfo info ,String msg) {
    switch(mType) {
        case WsClientComposer:
        return _genClientControlMessage(info,
                                        createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PONG);

        case WsServerComposer:
        return _genServerControlMessage(info,
                                        createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PONG);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genCloseMessage(WebSocketClientInfo info,String msg) {
    switch(mType) {
        case WsClientComposer:
        return _genClientControlMessage(info,
                                        createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE);

        case WsServerComposer:
        return _genServerControlMessage(info,
                                        createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::_genClientControlMessage(WebSocketClientInfo info,ByteArray payload,int type) {
    ByteArray sink = createByteArray(payload->size() + 64);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::B0_FLAG_FIN | type;
    sinkWriter->writeByte(b0);

    int b1 = payload->size();
    b1 |= st(WebSocketProtocol)::B1_FLAG_MASK;
    sinkWriter->writeByte(b1);

    ByteArray maskKey = createByteArray(4);
    mRand->nextBytes(maskKey);
    sinkWriter->writeByteArray(maskKey);

    if (payload != nullptr) {
        ByteArray maskBuff = createByteArray(payload);
        st(WebSocketProtocol)::toggleMask(maskBuff,maskKey);
        sinkWriter->writeByteArray(maskBuff);
    }
    
    sink->qucikShrink(sinkWriter->getIndex());
    return sink;
}

ByteArray _WebSocketHybi13Composer::_genServerControlMessage(WebSocketClientInfo info,ByteArray payload,int type) {
    ByteArray sink = createByteArray(payload->size() + 64);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::B0_FLAG_FIN | type;
    sinkWriter->writeByte(b0);

    int b1 = payload->size();
    sinkWriter->writeByte(b1);
    if (payload != nullptr) {
        sinkWriter->writeByteArray(payload);
    }
    sink->qucikShrink(sinkWriter->getIndex());
    return sink;
}

}
