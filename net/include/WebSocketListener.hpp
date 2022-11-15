#ifndef __OBOTCHA_WEB_SOCKET_LISTENER_HPP__
#define __OBOTCHA_WEB_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "WebSocketFrame.hpp"

namespace obotcha {

class _WebSocketLinker;

DECLARE_CLASS(WebSocketListener) {
public:
    //for server
    virtual int onData(WebSocketFrame frame,sp<_WebSocketLinker> client){return 0;}

    virtual int onConnect(sp<_WebSocketLinker> client) {return 0;}

    virtual int onDisconnect(sp<_WebSocketLinker> client) {return 0;}

    virtual bool onPong(String,sp<_WebSocketLinker> client) {return true;}

    virtual bool onPing(String,sp<_WebSocketLinker> client)  {return true;}

    //for client
    virtual int onData(WebSocketFrame frame){return 0;}

    virtual int onConnect() {return 0;}

    virtual int onDisconnect() {return 0;}

    virtual bool onPong(String) {return true;}

    virtual bool onPing(String)  {return true;}

    ~_WebSocketListener(){}
};

}
#endif
