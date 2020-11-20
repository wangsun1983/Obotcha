#ifndef __OBOTCHA_WEB_SOCKET_COMPOSER_HPP__
#define __OBOTCHA_WEB_SOCKET_COMPOSER_HPP__

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

#define MAX_WEBSOCKET_FRAME_SIZE 64*1024

enum WebSocketFrameComposerType {
    WsClientComposer = 1,
    WsServerComposer
};

DECLARE_SIMPLE_CLASS(WebSocketComposer) {
public:
    _WebSocketComposer(int version,int maxframesize):mType(version),mMaxFrameSize(maxframesize) {}
    
    int getMaxFrameSize() {return mMaxFrameSize;}

    void setMaxFrameSzie(int frame) {mMaxFrameSize = frame;}

    virtual ByteArray genShakeHandMessage(WebSocketClientInfo) = 0;
    
    virtual ArrayList<ByteArray> genTextMessage(WebSocketClientInfo,String) = 0;

    virtual ArrayList<ByteArray> genBinaryMessage(WebSocketClientInfo,ByteArray) = 0;

    virtual ByteArray genPingMessage(WebSocketClientInfo,String) = 0;

    virtual ByteArray genPongMessage(WebSocketClientInfo,String) = 0;

    virtual ByteArray genCloseMessage(WebSocketClientInfo,String) = 0;

protected:
    int mType;
    int mMaxFrameSize;

    void toggleMask(ByteArray buffer, ByteArray key) {
        int keyLength = key->size();
        int byteCount = buffer->size();
        int frameBytesRead = 0;
        for (int i = 0; i < byteCount; i++, frameBytesRead++) {
            int keyIndex = (int) (frameBytesRead % keyLength);
            buffer->fill(i,(byte) (buffer->at(i) ^ key->at(keyIndex)));
        }
    }
};

}
#endif
