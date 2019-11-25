#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi07Composer.hpp"

namespace obotcha {
_WebSocketHybi07Composer::_WebSocketHybi07Composer(int type):_WebSocketHybi08Composer(type),
                                                             _WebSocketHybi13Composer(type),
                                                             _WebSocketComposer(type) {

}

}

