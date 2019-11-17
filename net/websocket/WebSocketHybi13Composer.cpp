#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketProtocol.hpp"

namespace obotcha {

_WebSocketHybi13Composer::_WebSocketHybi13Composer() {
    mSha = createSha(SHA_1);
    mBase64 = createBase64();
}

String _WebSocketHybi13Composer::genShakeHandMessage(HttpHeader h) {
    
    //TODO
    switch(mType) {
        case WsClientComposer:
        return genClientShakeHandMessage(h);

        case WsServerComposer:
        return genServerShakeHandMessage(h);
    }

    return nullptr;

}

String _WebSocketHybi13Composer::genClientShakeHandMessage(HttpHeader h) {
    //TODO
}

String _WebSocketHybi13Composer::genServerShakeHandMessage(HttpHeader h) {
    String key = h->getValue(Http_Header_Sec_WebSocket_Key);

    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    //printf("key_mgic is %s \n",key_mgic->toChars());
    ByteArray sha1_content = mSha->encryptRawData(createByteArray(key_mgic));
    //printf("sha1_content is %s \n",sha1_content->toValue());
    String base64 = mBase64->encode(sha1_content)->toString();
    //printf("base64 is %s \n",base64->toChars());

    String head = "HTTP/1.1 101 Switching Protocols\r\n";
    String upgrade = head->append("Upgrade: websocket\r\n");
    String connection = upgrade->append("Connection: Upgrade\r\n");

    String protocols = h->getValue(Http_Header_Sec_WebSocket_Protocol);
    if(protocols != nullptr) {
        connection = connection->append("Sec-WebSocket-Protocol:")->append(protocols)->append("\r\n\r\n");
    }

    String resp = connection->append("Sec-WebSocket-Accept:")->append(base64)->append("\r\n\r\n");

    //printf("generate shake resp is %s \n",resp->toChars());
    return resp;
}

}
