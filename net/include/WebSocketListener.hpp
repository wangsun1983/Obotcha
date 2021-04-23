#ifndef __OBOTCHA_WEB_SOCKET_LISTENER_HPP__
#define __OBOTCHA_WEB_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"

namespace obotcha {

class _WebSocketClientInfo;

enum PingResult {
    PingResultResponse,
    PingResultNoResponse
};

DECLARE_SIMPLE_CLASS(WebSocketListener) {
public:
    virtual int onData(WebSocketFrame frame,sp<_WebSocketClientInfo> client = nullptr) = 0;

    virtual int onConnect(sp<_WebSocketClientInfo> client = nullptr) = 0;

    virtual int onDisconnect(sp<_WebSocketClientInfo> client = nullptr) = 0;

    virtual int onPong(String,sp<_WebSocketClientInfo> client = nullptr) {return PingResultResponse;}

    virtual int onPing(String,sp<_WebSocketClientInfo> client = nullptr)  {return PingResultResponse;}
};

}
#endif
