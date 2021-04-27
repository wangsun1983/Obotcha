#ifndef __OBOTCHA_WEB_SOCKET_LISTENER_HPP__
#define __OBOTCHA_WEB_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"

namespace obotcha {

class _WebSocketLinker;

enum PingResult {
    PingResultResponse = 0,
    PingResultNoResponse
};

DECLARE_SIMPLE_CLASS(WebSocketListener) {
public:
    //for server
    virtual int onData(WebSocketFrame frame,sp<_WebSocketLinker> client){return 0;}

    virtual int onConnect(sp<_WebSocketLinker> client) {return 0;}

    virtual int onDisconnect(sp<_WebSocketLinker> client) {return 0;}

    virtual int onPong(String,sp<_WebSocketLinker> client) {return PingResultResponse;}

    virtual int onPing(String,sp<_WebSocketLinker> client)  {return PingResultResponse;}

    //for client
    virtual int onData(WebSocketFrame frame){return 0;}

    virtual int onConnect() {return 0;}

    virtual int onDisconnect() {return 0;}

    virtual int onPong(String) {return PingResultResponse;}

    virtual int onPing(String)  {return PingResultResponse;}
};

}
#endif
