#ifndef __WEB_SOCKET_COMPOSER_HPP__
#define __WEB_SOCKET_COMPOSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "WebSocketClientInfo.hpp"

namespace obotcha {

enum WebSocketFrameComposerType {
    WsClientComposer = 1,
    WsServerComposer
};


DECLARE_SIMPLE_CLASS(WebSocketComposer) {
public:
    _WebSocketComposer(int);
    virtual String genShakeHandMessage(WebSocketClientInfo) = 0;
    //virtual String genMessageFrame() = 0;
protected:
    int mType;    
};

}
#endif
