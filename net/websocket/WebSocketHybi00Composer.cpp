#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

_WebSocketHybi00Composer::_WebSocketHybi00Composer(int type,int maxFrameSize)
:_WebSocketComposer(type,maxFrameSize) {

}

String _WebSocketHybi00Composer::genShakeHandMessage(WebSocketClientInfo) {
    //TODO
    return nullptr;
}

String _WebSocketHybi00Composer::genTextMessage(WebSocketClientInfo,String) {
    //TODO
    return nullptr;
}

}

