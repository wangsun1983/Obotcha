#include "WebSocketHybi00Validator.hpp"

namespace obotcha {

bool _WebSocketHybi00Validator::validateHandShake(HttpHeader h) {
    String method = h->get(st(HttpHeader)::Method);
    if(h == nullptr || !method->equalsIgnoreCase("GET")) {
        return false;
    }

    if(h->get(st(HttpHeader)::SecWebSocketKey1) == nullptr
      ||h->get(st(HttpHeader)::SecWebSocketKey2) == nullptr
      ||h->get(st(HttpHeader)::SecWebSocketKey3) == nullptr) {
          return false;
    }

    return true;
}

WebSocketPermessageDeflate _WebSocketHybi00Validator::validateExtensions(HttpHeader) {
    return nullptr;
}

bool _WebSocketHybi00Validator::validateEntirePacket(ByteArray pack) {
    return false;
}

ArrayList<String> _WebSocketHybi00Validator::extractSubprotocols(HttpHeader h) {
    ArrayList<String> protocols = createArrayList<String>();
    String protocolstr = h->get(st(HttpHeader)::SecWebSocketProtocol);
    if(protocolstr == nullptr) {
        return nullptr;
    }

    return protocolstr->trimAll()->split(",");
}

HttpResponse _WebSocketHybi00Validator::createServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols,WebSocketPermessageDeflate deflate) {
    return nullptr;
}

HttpRequest _WebSocketHybi00Validator::createClientShakeHandMessage(HttpUrl) {
    return nullptr;
}

}
