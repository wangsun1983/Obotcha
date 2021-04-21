#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

_WebSocketHybi00Composer::_WebSocketHybi00Composer(int type,int ver,int maxFrameSize)
:_WebSocketComposer(type,ver,maxFrameSize) {

}

ByteArray _WebSocketHybi00Composer::genClientShakeHandMessage(HttpUrl) {
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genServerShakeHandMessage(String SecWebSocketKey,String protocols) {
    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi00Composer::genTextMessage(WebSocketClientInfo,String) {
    //TODO
    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi00Composer::genBinaryMessage(WebSocketClientInfo,ByteArray) {
    //TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genPingMessage(WebSocketClientInfo,String) {
    //TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genPongMessage(WebSocketClientInfo,String) {
    //TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genCloseMessage(WebSocketClientInfo,String) {
    //TODO
    return nullptr;
}


}

