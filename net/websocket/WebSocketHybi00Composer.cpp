#include "WebSocketHybi00Composer.hpp"

namespace obotcha {

_WebSocketHybi00Composer::_WebSocketHybi00Composer(_WebSocketProtocol::Model model, int ver,
                                                   int maxFrameSize)
    : _WebSocketComposer(model, ver, maxFrameSize) {}

HttpRequest _WebSocketHybi00Composer::genClientShakeHandMessage(HttpUrl) const {
    return nullptr;
}

HttpResponse
_WebSocketHybi00Composer::genServerShakeHandMessage(String,ArrayList<String>) const {
    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi00Composer::genTextMessage(String) {
    return nullptr;
}

ArrayList<ByteArray> _WebSocketHybi00Composer::genBinaryMessage(ByteArray) {
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genPingMessage(String) {
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genPongMessage(String) {
    return nullptr;
}

ByteArray _WebSocketHybi00Composer::genCloseMessage(String) {
    return nullptr;
}

} // namespace obotcha
