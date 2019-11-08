#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "WebSocketParser.hpp"

namespace obotcha {

void _WebSocketParser::setParseData(ByteArray data) {
    mData = data;
    mReader = createByteArrayReader(data);
    isClient = false;
}

void _WebSocketParser::setAsClient() {
    isClient = true;
}

}
