#include "WebSocketHybi00Validator.hpp"
#include "Inspect.hpp"

namespace obotcha {

bool _WebSocketHybi00Validator::validateHandShake(HttpHeader h) {

    return h != nullptr && h->get(st(HttpHeader)::Method)->equalsIgnoreCase("GET")
        && h->get(st(HttpHeader)::SecWebSocketKey1) != nullptr
        && h->get(st(HttpHeader)::SecWebSocketKey2) != nullptr
        && h->get(st(HttpHeader)::SecWebSocketKey3) != nullptr;
}

WebSocketPermessageDeflate _WebSocketHybi00Validator::validateExtensions(HttpHeader) {
    return nullptr;
}

bool _WebSocketHybi00Validator::validateEntirePacket(ByteArray pack) {
    return false;
}

ArrayList<String> _WebSocketHybi00Validator::extractSubprotocols(HttpHeader h) {
    String protocolstr = h->get(st(HttpHeader)::SecWebSocketProtocol);
    Inspect(protocolstr == nullptr,nullptr)
    return protocolstr->trimAll()->split(",");
}

HttpResponse _WebSocketHybi00Validator::createServerShakeHandMessage(String SecWebSocketKey,
                                                                    ArrayList<String> protocols,
                                                                    WebSocketPermessageDeflate deflate) {
    return nullptr;
}

HttpRequest _WebSocketHybi00Validator::createClientShakeHandMessage(HttpUrl) {
    return nullptr;
}

}
