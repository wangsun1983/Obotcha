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

namespace obotcha {

enum WebSocketFrameComposerType {
    WsClientComposer = 1,
    WsServerComposer
};


DECLARE_SIMPLE_CLASS(WebSocketComposer) {
public:
    virtual String genShakeHandMessage() = 0;
    //virtual String genMessageFrame() = 0;
    void setType(int);

protected:
    int mType;
};

}
#endif
