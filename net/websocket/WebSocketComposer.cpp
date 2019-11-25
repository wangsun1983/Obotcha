#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "WebSocketComposer.hpp"

namespace obotcha {

_WebSocketComposer::_WebSocketComposer(int v) {
    mType = v;
}

}
