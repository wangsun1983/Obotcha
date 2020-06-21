#ifndef __OBOTCHA_WEB_SOCKET_LISTENER_HPP__
#define __OBOTCHA_WEB_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"

namespace obotcha {

class _WebSocketClientInfo;

enum PingResult {
    PingResultResponse,
    PingResultNoResponse
};

DECLARE_SIMPLE_CLASS(WebSocketListener) {
public:
    virtual int onMessage(sp<_WebSocketClientInfo> client,String message) = 0;

    virtual int onData(sp<_WebSocketClientInfo> client,ByteArray data) = 0;

    virtual int onConnect(sp<_WebSocketClientInfo> client) = 0;

    virtual int onDisconnect(sp<_WebSocketClientInfo> client) = 0;

    virtual int onPong(sp<_WebSocketClientInfo> client,String) {return PingResultResponse;}

    virtual int onPing(sp<_WebSocketClientInfo> client,String)  {return PingResultResponse;}
};

}
#endif
