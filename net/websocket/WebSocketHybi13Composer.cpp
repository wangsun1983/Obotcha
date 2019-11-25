#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketProtocol.hpp"

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

String _WebSocketHybi13Composer::genClientShakeHandMessage(WebSocketClientInfo info) {
    //TODO
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
        connection = connection->append("Sec-WebSocket-Protocol:")->append(protocols)->append("\r\n\r\n");
    }

    String resp = connection->append("Sec-WebSocket-Accept:")->append(base64)->append("\r\n\r\n");

    //check whetehr we have Deflate
    printf("genServerShakeHandeMessage trace1 \n");
    if(info->mDeflate != nullptr) {
        printf("genServerShakeHandeMessage trace2 \n");
        resp = resp->append("permessage-deflate")
                   ->append(",client_max_window_bits=")
                   ->append(createString(info->mDeflate->getServerMaxWindowBits()));
    }

    return resp;
}

}
