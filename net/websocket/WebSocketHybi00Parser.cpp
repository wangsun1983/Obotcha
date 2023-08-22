#include "WebSocketHybi00Parser.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 00
/**
 * There are many differences between Hybi 00 and Hybi 13
 */
bool _WebSocketHybi00Parser::parseHeader(){
    return false;
}

bool _WebSocketHybi00Parser::parseContent(bool) {
    return false;
}

bool _WebSocketHybi00Parser::parsePingBuff() {
    return false;
}

bool _WebSocketHybi00Parser::parsePongBuff() {
    return false;
}

String _WebSocketHybi00Parser::getOrigin(HttpHeader) {
    return nullptr;
}

int _WebSocketHybi00Parser::getVersion() {
    return 0;
}

ByteArray _WebSocketHybi00Parser::parseContinuationContent(ByteArray) {
    return nullptr;
}

}

