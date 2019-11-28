#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi07Composer.hpp"

namespace obotcha {
_WebSocketHybi07Composer::_WebSocketHybi07Composer(int type,int maxframe):_WebSocketHybi08Composer(type,maxframe),
                                                             _WebSocketHybi13Composer(type,maxframe),
                                                             _WebSocketComposer(type,maxframe) {

}

}

