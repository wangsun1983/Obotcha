#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi08Composer.hpp"

namespace obotcha {

_WebSocketHybi08Composer::_WebSocketHybi08Composer(int type):_WebSocketHybi13Composer(type),
                                                             _WebSocketComposer(type) {

}

}

