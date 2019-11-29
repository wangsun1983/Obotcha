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
        return genClientShakeHandMessage(h);

        case WsServerComposer:
        return genServerShakeHandMessage(h);
    }

    return nullptr;
}

ByteArray _WebSocketHybi13Composer::genClientShakeHandMessage(WebSocketClientInfo client) {
    printf("genClientShakeHandMessage trace1\n");
    HttpUrl httpUrl = st(HttpUrlParser)::parseUrl(client->mConnectUrl);
    HttpPacket packet = createHttpPacket();
    packet->setMethod(HttpMethodGet);
    packet->setHeader(client->mHttpHeader);
    packet->setUrl(httpUrl->getPath());
    packet->setMajorVersion(1);
    packet->setMinorVersion(1);

    String host = httpUrl->getHost()->append(":")->append(createString(httpUrl->getPort()));
    packet->getHeader()->setValue(Http_Header_Host,host);
    packet->getHeader()->setValue(Http_Header_Sec_WebSocket_Version,"13");
    if(packet->getHeader()->getValue(Http_Header_Accept) == nullptr) {
        packet->getHeader()->setValue(Http_Header_Accept,"*/*");
    }

    if(packet->getHeader()->getValue(Http_Header_Accept_Language) == nullptr) {
        packet->getHeader()->setValue(Http_Header_Accept_Language,"en-US,en;q=0.5");
    }

    if(packet->getHeader()->getValue(Http_Header_Accept_Encoding) == nullptr) {
        packet->getHeader()->setValue(Http_Header_Accept_Encoding,"gzip, deflate");
    }

    if(packet->getHeader()->getValue(Http_Header_Origin) == nullptr) {
        packet->getHeader()->setValue(Http_Header_Origin,"null");
    }

    if(packet->getHeader()->getValue(Http_Header_Sec_WebSocket_Key) == nullptr) {
        //we should gen a sec key
        Random rand = createRandom();
        int v = rand->nextInt();
        Base64 base64key = createBase64();
        String key = base64key->decode(createString(v));
        printf("sec websocket key is %s \n",key->toChars());
        packet->getHeader()->setValue(Http_Header_Sec_WebSocket_Key,key);
    }

    if(packet->getHeader()->getValue(Http_Header_Connection) == nullptr) {
        packet->getHeader()->setValue(Http_Header_Connection,"keep-alive, Upgrade");
    }

    if(packet->getHeader()->getValue(Http_Header_Upgrade) == nullptr) {
        packet->getHeader()->setValue(Http_Header_Upgrade,"websocket");
    }

    if(packet->getHeader()->getValue(Http_Header_Pragma) == nullptr) {
        packet->getHeader()->setValue(Http_Header_Pragma,"no-cache");
    }

    if(packet->getHeader()->getValue(Http_Header_Cache_Control) == nullptr) {
        packet->getHeader()->setValue(Http_Header_Cache_Control,"no-cache");
    }
    printf("genClientShakeHandMessage trace2\n");
    
    return createByteArray(packet->genHttpRequest());
}

ByteArray _WebSocketHybi13Composer::genServerShakeHandMessage(WebSocketClientInfo  info) {
    HttpHeader h = info->mHttpHeader;
    String key = h->getValue(Http_Header_Sec_WebSocket_Key);

    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    ByteArray sha1_content = mSha->encryptRawData(createByteArray(key_mgic));
    String base64 = mBase64->encode(sha1_content)->toString();
    
    String head = "HTTP/1.1 101 Switching Protocols\r\n";
    String upgrade = head->append("Upgrade: websocket\r\n");
    String connection = upgrade->append("Connection: Upgrade\r\n");

    String protocols = h->getValue(Http_Header_Sec_WebSocket_Protocol);
    if(protocols != nullptr) {
        //TODO
        connection = connection->append("Sec-WebSocket-Protocol:")->append(protocols)->append("\r\n");
    }

    String resp = connection->append("Sec-WebSocket-Accept:")->append(base64)->append("\r\n");

    //check whetehr we have Deflate
    printf("genServerShakeHandeMessage trace1 \n");
   
    if(info->mDeflate != nullptr) {
        printf("genServerShakeHandeMessage trace2 \n");
        resp = resp->append("Sec-WebSocket-Extensions:")
                   ->append("permessage-deflate")
                   ->append(";client_max_window_bits=")
                   ->append(createString(info->mDeflate->getServerMaxWindowBits()))
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
        return genServerTextMessage(info,content);
    }

    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::_genClientMessage(WebSocketClientInfo info,ByteArray content,int type) {
    ArrayList<ByteArray> genResult = createArrayList<ByteArray>();

    ByteArray entireMessage = nullptr;
    if(info->mDeflate != nullptr) {
        entireMessage = info->mDeflate->compress(content);
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

        ByteArray sink = createByteArray(message->size() + 14);
        ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

        int b0 = 0;//formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
        if(isFirstFrame) {
            b0 = type;
        } else {
            b0 = st(WebSocketProtocol)::OPCODE_CONTINUATION;
        }

        if(isLastFrame) {
            b0 |= st(WebSocketProtocol)::B0_FLAG_FIN;
        }

        printf("b0 is %x \n",b0);
        sinkWriter->writeByte(b0);

        ByteArray maskKey = createByteArray(4);
        int b1 = st(WebSocketProtocol)::B1_FLAG_MASK;
        //random.nextBytes(maskKey);
        mRand->nextBytes(maskKey);
    
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

        sinkWriter->writeByteArray(maskKey);
        //writeMaskedSynchronized(buffer, byteCount);
        ByteArray maskBuff = createByteArray(message);
        printf("start toggleMask,maskBuff size is %d,message size is %d \n",maskBuff->size(),message->size());
        st(WebSocketProtocol)::toggleMask(maskBuff,maskKey);
        sinkWriter->writeByteArray(maskBuff);
        printf("finish toggleMask£¬index is %d \n",sinkWriter->getIndex());
        sink->qucikShrink(sinkWriter->getIndex());

        genResult->add(sink);

        if(isLastFrame) {
            break;
        }
    }

    return genResult;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genServerTextMessage(WebSocketClientInfo info,String c) {
    ArrayList<ByteArray> genResult = createArrayList<ByteArray>();

    ByteArray content = createByteArray(c);

    ByteArray sink = createByteArray(content->size() + 14);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::OPCODE_TEXT|st(WebSocketProtocol)::B0_FLAG_FIN;
    printf("b0 is %x \n",b0);
    sinkWriter->writeByte(b0);

    int b1 = 0;
    int byteCount = content->size();

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

    sinkWriter->writeByteArray(content);
    sink->qucikShrink(sinkWriter->getIndex());
    
    //TODO
    genResult->add(sink);
    return genResult;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genBinaryMessage(WebSocketClientInfo info,ByteArray content) {
    switch(mType) {
        case WsClientComposer:
        return _genClientMessage(info,content,st(WebSocketProtocol)::OPCODE_BINARY);

        case WsServerComposer:
        return genServerBinaryMessage(info,content);
    }

    return nullptr;
}


ArrayList<ByteArray> _WebSocketHybi13Composer::genServerBinaryMessage(WebSocketClientInfo info,ByteArray content) {
    //TODO
}

}
