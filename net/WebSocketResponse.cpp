#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "WebSocketResponse.hpp"
#include "WebSocketProtocol.hpp"
#include "Sha.hpp"

namespace obotcha {

_WebSocketResponse::_WebSocketResponse() {
    mSha = createSha(AbstractSHA1);
    mBase64 = createBase64();
}

String _WebSocketResponse::generateResponse() {
    //TODO
    return nullptr;
}

String _WebSocketResponse::generateShakeHandResponse(String key) {
    printf("key is %s \n",key->toChars());
    printf("accept magic is %s \n",st(WebSocketProtocol)::ACCEPT_MAGIC->toChars());
    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    printf("key_mgic is %s \n",key_mgic->toChars());
    ByteArray sha1_content = mSha->encryptRawData(createByteArray(key_mgic));
    printf("sha1_content is %s \n",sha1_content->toValue());
    String base64 = mBase64->encode(sha1_content)->toString();
    printf("base64 is %s \n",base64->toChars());

    String head = "HTTP/1.1 101 Switching Protocols\r\n";
    String upgrade = head->append("Upgrade: websocket\r\n");
    String connection = upgrade->append("Connection: Upgrade\r\n");
    String resp = connection->append("Sec-WebSocket-Accept:")->append(base64)->append("\r\n\r\n");

    //printf("generate shake resp is %s \n",resp->toChars());
    return resp;
}

}

