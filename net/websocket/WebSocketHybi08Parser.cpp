#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "InetAddress.hpp"
#include "String.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketParser.hpp"

namespace obotcha {

String _WebSocketHybi08Parser::getOrigin(HttpHeader h) {
    return h->get(st(HttpHeader)::SecWebSocketOrigin);
}

int _WebSocketHybi08Parser::getVersion() { return 8; }

} // namespace obotcha
