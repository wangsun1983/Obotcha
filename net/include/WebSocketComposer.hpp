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

#define MAX_WEBSOCKET_FRAME_SIZE 256*1024

enum WebSocketFrameComposerType {
    WsClientComposer = 1,
    WsServerComposer
};

DECLARE_SIMPLE_CLASS(WebSocketComposer) {
public:
    _WebSocketComposer(int version,int maxframesize);
    
    int getMaxFrameSize();

    void setMaxFrameSzie(int);

    virtual ByteArray genShakeHandMessage(WebSocketClientInfo) = 0;
    
    virtual ArrayList<ByteArray> genTextMessage(WebSocketClientInfo,String) = 0;

    virtual ArrayList<ByteArray> genBinaryMessage(WebSocketClientInfo,ByteArray) = 0;
    //virtual String genControlMessage(WebSocketClientInfo,int opcode,String);
    //virtual String genBinaryMessage(WebSocketClientInfo,int opcode,String);
    //virtual String genMessageFrame() = 0;
protected:
    int mType;
    int mMaxFrameSize;
};

}
#endif
