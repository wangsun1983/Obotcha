#ifndef __WEB_SOCKET_CLIENT_INFO_HPP__
#define __WEB_SOCKET_CLIENT_INFO_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

class _WebSocketComposer;
class _WebSocketParser;
class _WebSocketPermessageDeflate;

DECLARE_SIMPLE_CLASS(WebSocketClientInfo) {
public:
    _WebSocketClientInfo();

    sp<_WebSocketParser> mParser;
    sp<_WebSocketComposer> mComposer;
    
    HttpHeader mHttpHeader;
    WebSocketHeader mWsHeader;
    sp<_WebSocketPermessageDeflate> mDeflate;
    ArrayList<String> mProtocols;
};

}
#endif
