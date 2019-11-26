#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketProtocol.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_WebSocketHybi13Composer::_WebSocketHybi13Composer(int type):_WebSocketComposer(type){
    mSha = createSha(SHA_1);
    mBase64 = createBase64();
}

String _WebSocketHybi13Composer::genShakeHandMessage(WebSocketClientInfo h) {
    
    //TODO
    switch(mType) {
        case WsClientComposer:
        return genClientShakeHandMessage(h);

        case WsServerComposer:
        return genServerShakeHandMessage(h);
    }

    return nullptr;
}

String _WebSocketHybi13Composer::genClientShakeHandMessage(WebSocketClientInfo h) {
    //TODO
    return nullptr;
}

String _WebSocketHybi13Composer::genTextMessage(WebSocketClientInfo info,String content) {
    switch(mType) {
        case WsClientComposer:
        return genClientTextMessage(info,content);

        case WsServerComposer:
        return genServerTextMessage(info,content);
    }

    return nullptr;
}

String _WebSocketHybi13Composer::genClientTextMessage(WebSocketClientInfo info,String content) {
    //TODO
}

String _WebSocketHybi13Composer::genServerTextMessage(WebSocketClientInfo info,String c) {
    //do zip!!!
    ByteArray content;
    //if(info->mDeflate != nullptr) {
    //    content = info->mDeflate->compress(createByteArray(c));
    //} else {
        content = createByteArray(c);
    //}

    ByteArray sink = createByteArray(content->size() + 14);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    //int b0 = formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
    int b0 = st(WebSocketProtocol)::OPCODE_TEXT|st(WebSocketProtocol)::B0_FLAG_FIN;
    printf("b0 is %x \n",b0);
    sinkWriter->writeByte(b0);

    int b1 = 0;
    int byteCount = content->size();
    //printf("byteCount is %d£¬message is %s \n",byteCount,message->toString()->toChars());
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
    
    return sink->toString();
}

String _WebSocketHybi13Composer::genServerShakeHandMessage(WebSocketClientInfo  info) {
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

    return resp;
}

}
