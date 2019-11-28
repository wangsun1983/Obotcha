#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketComposer.hpp"
#include "WebSocketClientInfo.hpp"
#include "WebSocketPermessageDeflate.hpp"

namespace obotcha {


_WebSocketClientInfo::_WebSocketClientInfo() {
    mParser = nullptr;
    mComposer = nullptr;
    mHttpHeader = createHttpHeader();
    mWsHeader = createWebSocketHeader();
    mDeflate = nullptr;
    mProtocols = nullptr;
}

}

