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
#include "HttpRequestWriter.hpp"
#include "HttpRequest.hpp"
#include "HttpPacketBuilder.hpp"
#include "HttpStatus.hpp"

namespace obotcha {

_WebSocketHybi13Composer::_WebSocketHybi13Composer(int type,int ver,int maxFrameSize):_WebSocketComposer(type,ver,maxFrameSize){
    mSha = createSha(SHA_1);
    mBase64 = createBase64();
    mRand = createRandom();
}

HttpRequest _WebSocketHybi13Composer::genClientShakeHandMessage(HttpUrl httpUrl) {
    HttpRequest packet = createHttpRequest();
    packet->getHeader()->setMethod(st(HttpMethod)::Get);
    //packet->setHeader(client->getHttpHeader());
    packet->getHeader()->setUrl(httpUrl);
    packet->getHeader()->setVersion(createHttpVersion(1,1));

    String host = httpUrl->getHost()->append(":",createString(httpUrl->getPort()));
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

    return packet;
}

HttpResponse _WebSocketHybi13Composer::genServerShakeHandMessage(String SecWebSocketKey,String protocols) {
    String key = SecWebSocketKey;
    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    ByteArray sha1_content = mSha->encryptRawData(createByteArray(key_mgic));
    String base64 = mBase64->encode(sha1_content)->toString();

    HttpPacketBuilder builder = createHttpPacketBuilder();
    builder->setVersion(1,1)
        ->setResponseStatus(st(HttpStatus)::SwitchProtocls)
        ->setResponseReason(st(HttpStatus)::toString(st(HttpStatus)::SwitchProtocls))
        ->addHeaderValue(st(HttpHeader)::SecWebSocketAccept,base64);

    if(protocols != nullptr) {
        builder->addHeaderValue(st(HttpHeader)::SecWebSocketProtocol,protocols);
    }

    if(mDeflate != nullptr) {
        String extension = createString("permessage-deflate")->append(";client_max_window_bits=",
                            createString(mDeflate->getServerMaxWindowBits()));

        builder->addHeaderValue(st(HttpHeader)::SecWebSocketExtensions,extension);
    }

    return builder->newHttpResponse();
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genTextMessage(String content) {
    switch(mType) {
        case WsClientComposer:
        return _genClientMessage(createByteArray(content),st(WebSocketProtocol)::OPCODE_TEXT);

        case WsServerComposer:
        return _genServerMessage(createByteArray(content),st(WebSocketProtocol)::OPCODE_TEXT);
    }

    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::_genClientMessage(ByteArray content,int type) {
    ArrayList<ByteArray> genResult = createArrayList<ByteArray>();

    ByteArray entireMessage = nullptr;
    
    if(mDeflate != nullptr) {
        entireMessage = mDeflate->compress(content);
    } else {
        entireMessage = content;
    }

    const byte *pData = entireMessage->toValue();
    int index = 0;
    bool isFirstFrame = true;
    bool isLastFrame = false;
    while(1) {
        int len = (entireMessage->size()-index) > mMaxFrameSize?mMaxFrameSize:(entireMessage->size() - index);
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

        sinkWriter->writeByte(b0);
        
        ByteArray maskKey = createByteArray(4);
        int b1 = 0;
        
        //client message need use mask.
        b1 = st(WebSocketProtocol)::B1_FLAG_MASK;
        mRand->nextBytes(maskKey);
    
        int byteCount = message->size();
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

        //client message need use mask.
        sinkWriter->writeByteArray(maskKey);
        ByteArray maskBuff = createByteArray(message);
        toggleMask(maskBuff,maskKey);
        sinkWriter->writeByteArray(maskBuff);
        
        sink->quickShrink(sinkWriter->getIndex());

        genResult->add(sink);

        if(isLastFrame) {
            break;
        }
    }

    return genResult;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::_genServerMessage(ByteArray content,int type) {
    ArrayList<ByteArray> genResult = createArrayList<ByteArray>();

    ByteArray entireMessage = content;

    const byte *pData = entireMessage->toValue();
    int index = 0;
    bool isFirstFrame = true;
    bool isLastFrame = false;
    while(1) {
        int len = (entireMessage->size()-index) > mMaxFrameSize?mMaxFrameSize:(entireMessage->size() - index);
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

        sinkWriter->writeByte(b0);

        int b1 = message->size();
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
        sink->quickShrink(sinkWriter->getIndex());

        genResult->add(sink);

        if(isLastFrame) {
            break;
        }
    }

    return genResult;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genBinaryMessage(ByteArray content) {
    switch(mType) {
        case WsClientComposer:
        return _genClientMessage(content,st(WebSocketProtocol)::OPCODE_BINARY);

        case WsServerComposer:
        return _genServerMessage(content,st(WebSocketProtocol)::OPCODE_BINARY);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genPingMessage(String msg) {
    switch(mType) {
        case WsClientComposer:
        return _genClientControlMessage(createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PING);

        case WsServerComposer:
        return _genServerControlMessage(createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PING);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genPongMessage(String msg) {
    switch(mType) {
        case WsClientComposer:
        return _genClientControlMessage(createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PONG);

        case WsServerComposer:
        return _genServerControlMessage(createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PONG);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genCloseMessage(String msg) {
    switch(mType) {
        case WsClientComposer:
        return _genClientControlMessage(createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE);

        case WsServerComposer:
        return _genServerControlMessage(createByteArray(msg),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::_genClientControlMessage(ByteArray payload,int type) {
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
        toggleMask(maskBuff,maskKey);
        sinkWriter->writeByteArray(maskBuff);
    }
    
    sink->quickShrink(sinkWriter->getIndex());
    return sink;
}

ByteArray _WebSocketHybi13Composer::_genServerControlMessage(ByteArray payload,int type) {
    ByteArray sink = createByteArray(payload->size() + 64);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::B0_FLAG_FIN | type;
    sinkWriter->writeByte(b0);

    int b1 = payload->size();
    sinkWriter->writeByte(b1);
    if (payload != nullptr) {
        sinkWriter->writeByteArray(payload);
    }
    sink->quickShrink(sinkWriter->getIndex());
    return sink;
}

}
