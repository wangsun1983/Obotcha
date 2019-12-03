#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 00
/**
 * There are many differences between Hybi 00 and Hybi 13
 */
WebSocketHeader _WebSocketHybi00Parser::parseHeader(){
    //TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Parser::parseContent(bool) {
    //TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Parser::parsePingBuff() {
    //TODO
    return nullptr;
}

ByteArray _WebSocketHybi00Parser::parsePongBuff() {
    //TODO
    return nullptr;
}

String _WebSocketHybi00Parser::getOrigin(HttpHeader) {
    return nullptr;
}

int _WebSocketHybi00Parser::getVersion() {
    return 0;
}

bool _WebSocketHybi00Parser::validateHandShake(HttpHeader h) {

    String method = h->getValue(Http_Header_Method);
    if(h == nullptr || !method->equalsIgnoreCase("GET")) {
        return false;
    }

    if(h->getValue(Http_Header_Sec_WebSocket_Key1) == nullptr
      ||h->getValue(Http_Header_Sec_WebSocket_Key2) == nullptr
      ||h->getValue(Http_Header_Sec_WebSocket_Key3) == nullptr) {
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
    String protocolstr = h->getValue(Http_Header_Sec_WebSocket_Protocol);
    if(protocolstr == nullptr) {
        return nullptr;
    }

    return protocolstr->trimAll()->split(",");
}

}

