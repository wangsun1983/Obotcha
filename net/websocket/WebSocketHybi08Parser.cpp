#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi08Parser.hpp"

namespace obotcha {

String _WebSocketHybi08Parser::getOrigin(HttpHeader h) {
    return h->getValue(Http_Header_Sec_WebSocket_Origin);
}

int _WebSocketHybi08Parser::getVersion() {
    return 8;
}

}

