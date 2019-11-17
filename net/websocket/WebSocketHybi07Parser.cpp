#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi07Parser.hpp"

namespace obotcha {

int _WebSocketHybi07Parser::getVersion() {
    return 7;
}

}

