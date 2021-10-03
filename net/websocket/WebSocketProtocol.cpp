#include "Object.hpp"
#include "StrongPointer.hpp"

#include "WebSocketProtocol.hpp"

namespace obotcha {
const String _WebSocketProtocol::ACCEPT_MAGIC =
    createString("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
}
