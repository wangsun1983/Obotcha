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
#include "HttpPacket.hpp"
#include "Random.hpp"
#include "Base64.hpp"
#include "HttpPacketWriter.hpp"
#include "HttpRequest.hpp"
#include "HttpStatus.hpp"

namespace obotcha {

_WebSocketHybi13Composer::_WebSocketHybi13Composer(int type,int ver,int maxFrameSize):_WebSocketComposer(type,ver,maxFrameSize){
    mSha = createSha(SHA_1);
    mBase64 = createBase64();
    mRand = createRandom();
}

HttpRequest _WebSocketHybi13Composer::genClientShakeHandMessage(HttpUrl httpUrl) {
    HttpRequest packet = createHttpRequest();
    auto header = packet->getHeader();
    header->setMethod(st(HttpMethod)::Get);
    //packet->setHeader(client->getHttpHeader());
    header->setUrl(httpUrl);
    header->setVersion(createHttpHeaderVersion(1,1));

    String host = httpUrl->getHost()->append(":",createString(httpUrl->getPort()));
    header->set(st(HttpHeader)::Host,host);
    header->set(st(HttpHeader)::SecWebSocketVersion,createString("13"));
    //if(header->get(st(HttpHeader)::Accept) == nullptr) {
    if(header->getAccept() == nullptr) {
        header->set(st(HttpHeader)::Accept,createString("*/*"));
    }

    //if(header->get(st(HttpHeader)::AcceptLanguage) == nullptr) {
    if(header->getAcceptLanguage() == nullptr) {
        header->set(st(HttpHeader)::AcceptLanguage,createString("en-US,en;q=0.5"));
    }

    //if(header->getAcceptEncoding() == nullptr) {
    if(header->getAcceptEncoding() == nullptr) {
        header->set(st(HttpHeader)::AcceptEncoding,createString("gzip, deflate"));
    }

    //if(header->get(st(HttpHeader)::Origin) == nullptr) {
    //if(header->getOrigin() == nullptr) {
    //    header->set(st(HttpHeader)::Origin,createString("null"));
    //}

    //if(header->get(st(HttpHeader)::SecWebSocketKey) == nullptr) {
    if(header->getWebSocketKey() == nullptr) {
        //we should gen a sec key
        Random rand = createRandom();
        ByteArray array = createByteArray(16);
        rand->nextBytes(array);
        Base64 base64key = createBase64();
        ByteArray key = base64key->encode(array);
        header->set(st(HttpHeader)::SecWebSocketKey,key->toString());
    }

    //if(header->get(st(HttpHeader)::Connection) == nullptr) {
    if(header->getConnection() == nullptr) {
        header->set(st(HttpHeader)::Connection,createString("keep-alive, Upgrade"));
    }

    //if(header->get(st(HttpHeader)::Upgrade) == nullptr) {
    if(header->getUpgrade() == nullptr) {
        header->set(st(HttpHeader)::Upgrade,createString("websocket"));
    }

    if(header->get(st(HttpHeader)::Pragma) == nullptr) {
        header->set(st(HttpHeader)::Pragma,createString("no-cache"));
    }

    //if(header->get(st(HttpHeader)::CacheControl) == nullptr) {
    if(header->getCacheControl() == nullptr) {
        header->set(st(HttpHeader)::CacheControl,createString("no-cache"));
    }

    return packet;
}

HttpResponse _WebSocketHybi13Composer::genServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols) {
    String key = SecWebSocketKey;
    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    ByteArray sha1_content = mSha->encryptRawData(key_mgic->toByteArray());
    String base64 = mBase64->encode(sha1_content)->toString();

    HttpResponse response = createHttpResponse();
    response->getHeader()->setResponseReason(st(HttpStatus)::toString(st(HttpStatus)::SwitchProtocls));
    response->getHeader()->setResponseStatus(st(HttpStatus)::SwitchProtocls);

    response->getHeader()->set(st(HttpHeader)::SecWebSocketAccept,base64);
    response->getHeader()->setUpgrade(createString("websocket"));
    response->getHeader()->setConnection(createString("Upgrade"));

    if(protocols != nullptr) {
        HttpHeaderSecWebSocketProtocol protocol = createHttpHeaderSecWebSocketProtocol();
        protocol->set(protocols);
        response->getHeader()->setWebSocketProtocol(protocol);
    }

    if(mDeflate != nullptr) {
        String extension = createString("permessage-deflate")->append(";client_max_window_bits=",
                            createString(mDeflate->getServerMaxWindowBits()));

        response->getHeader()->set(st(HttpHeader)::SecWebSocketExtensions,extension);
    }

    return response;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genTextMessage(String content) {

    switch(mType) {
        case WsClientComposer:
        return _genClientMessage(content->toByteArray(),st(WebSocketProtocol)::OPCODE_TEXT);


        case WsServerComposer:
        return _genServerMessage(content->toByteArray(),st(WebSocketProtocol)::OPCODE_TEXT);
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
        ByteArrayWriter sinkWriter = createByteArrayWriter(sink,Global::BigEndian);

        int b0 = 0;
        if(isFirstFrame) {
            b0 = type;
            isFirstFrame = false;
        } else {
            b0 = st(WebSocketProtocol)::OPCODE_CONTINUATION;
        }

        if(isLastFrame) {
            b0 |= st(WebSocketProtocol)::B0_FLAG_FIN;
        }

        sinkWriter->write<byte>(b0);

        //wangsl
        if(mDeflate != nullptr) {
           b0 |= st(WebSocketProtocol)::B0_FLAG_RSV1;
        }
        //wangsl

        ByteArray maskKey = createByteArray(4);
        int b1 = 0;

        //client message need use mask.
        b1 = st(WebSocketProtocol)::B1_FLAG_MASK;
        mRand->nextBytes(maskKey);

        int byteCount = message->size();
        if (byteCount <= st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
            b1 |= (int) byteCount;
            sinkWriter->write<byte>(b1);
        } else if (byteCount <= st(WebSocketProtocol)::PAYLOAD_SHORT_MAX) {
            b1 |= st(WebSocketProtocol)::PAYLOAD_SHORT;
            sinkWriter->write<byte>(b1);
            sinkWriter->write<short int>((int) byteCount);
        } else {
            b1 |= st(WebSocketProtocol)::PAYLOAD_LONG;
            sinkWriter->write<byte>(b1);
            sinkWriter->write<long>(byteCount);
        }

        //client message need use mask.
        sinkWriter->write(maskKey);
        ByteArray maskBuff = createByteArray(message);
        toggleMask(maskBuff,maskKey);
        sinkWriter->write(maskBuff);

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

        sinkWriter->write<byte>(b0);

        int b1 = message->size();
        if (b1 <= st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
            sinkWriter->write<byte>(b1);
        } else if (b1 <= st(WebSocketProtocol)::PAYLOAD_SHORT_MAX) {
            sinkWriter->write<byte>(st(WebSocketProtocol)::PAYLOAD_SHORT);
            sinkWriter->write<short int>(b1);
        } else {
            sinkWriter->write<byte>(st(WebSocketProtocol)::PAYLOAD_BYTE_MAX);
            sinkWriter->write<long>(b1);
        }

        sinkWriter->write(message);
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
        return _genClientControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PING);

        case WsServerComposer:
        return _genServerControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PING);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genPongMessage(String msg) {
    switch(mType) {
        case WsClientComposer:
        return _genClientControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PONG);

        case WsServerComposer:
        return _genServerControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PONG);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genCloseMessage(String msg) {
    switch(mType) {
        case WsClientComposer:
        return _genClientControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE);

        case WsServerComposer:
        return _genServerControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::_genClientControlMessage(ByteArray payload,int type) {
    ByteArray sink = createByteArray(payload->size() + 64);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::B0_FLAG_FIN | type;
    sinkWriter->write<byte>(b0);

    int b1 = payload->size();
    b1 |= st(WebSocketProtocol)::B1_FLAG_MASK;
    sinkWriter->write<byte>(b1);

    ByteArray maskKey = createByteArray(4);
    mRand->nextBytes(maskKey);
    sinkWriter->write(maskKey);

    if (payload != nullptr) {
        ByteArray maskBuff = createByteArray(payload);
        toggleMask(maskBuff,maskKey);
        sinkWriter->write(maskBuff);
    }

    sink->quickShrink(sinkWriter->getIndex());
    return sink;
}

ByteArray _WebSocketHybi13Composer::_genServerControlMessage(ByteArray payload,int type) {
    ByteArray sink = createByteArray(payload->size() + 64);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::B0_FLAG_FIN | type;
    sinkWriter->write<byte>(b0);

    int b1 = payload->size();
    sinkWriter->write<byte>(b1);
    if (payload != nullptr) {
        sinkWriter->write(payload);
    }
    sink->quickShrink(sinkWriter->getIndex());
    return sink;
}

}
