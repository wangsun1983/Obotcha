#include "WebSocketHybi00Parser.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 00
/**
 * There are many differences between Hybi 00 and Hybi 13
 */
bool _WebSocketHybi00Parser::parseHeader(){
    //TODO
    return false;
}

bool _WebSocketHybi00Parser::parseContent(bool) {
    //TODO
    return false;
}

bool _WebSocketHybi00Parser::parsePingBuff() {
    //TODO
    return false;
}

bool _WebSocketHybi00Parser::parsePongBuff() {
    //TODO
    return false;
}

String _WebSocketHybi00Parser::getOrigin(HttpHeader) {
    return nullptr;
}

int _WebSocketHybi00Parser::getVersion() {
    return 0;
}

bool _WebSocketHybi00Parser::validateHandShake(HttpHeader h) {

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

ByteArray _WebSocketHybi00Parser::validateContinuationContent(ByteArray) {
    return nullptr;
}

bool _WebSocketHybi00Parser::validateEntirePacket(ByteArray pack) {
    //TODO
    return false;
}

WebSocketPermessageDeflate _WebSocketHybi00Parser::validateExtensions(HttpHeader) {
    return nullptr;
}

ArrayList<String> _WebSocketHybi00Parser::extractSubprotocols(HttpHeader h) {
    ArrayList<String> protocols = createArrayList<String>();
    String protocolstr = h->get(st(HttpHeader)::SecWebSocketProtocol);
    if(protocolstr == nullptr) {
        return nullptr;
    }

    return protocolstr->trimAll()->split(",");
}

}

