#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "HttpHeader.hpp"
#include "InetAddress.hpp"
#include "String.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketParser.hpp"

namespace obotcha {

_WebSocketHybi00Composer::_WebSocketHybi00Composer(int type, int ver,
                                                   int maxFrameSize)
    : _WebSocketComposer(type, ver, maxFrameSize) {}

HttpRequest _WebSocketHybi00Composer::genClientShakeHandMessage(HttpUrl) {
    return nullptr;
}

HttpResponse
_WebSocketHybi00Composer::genServerShakeHandMessage(String SecWebSocketKey,
                                                    ArrayList<String> protocols) {
    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi00Composer::genTextMessage(String) {
    // TODO
    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi00Composer::genBinaryMessage(ByteArray) {
    // TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genPingMessage(String) {
    // TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genPongMessage(String) {
    // TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genCloseMessage(String) {
    // TODO
    return nullptr;
}

} // namespace obotcha
