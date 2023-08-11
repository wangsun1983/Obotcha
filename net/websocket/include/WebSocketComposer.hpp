#ifndef __OBOTCHA_WEB_SOCKET_COMPOSER_HPP__
#define __OBOTCHA_WEB_SOCKET_COMPOSER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketComposer) {
public:
    static const int kMaxWebSocketFrameSize = 64*1024;

    _WebSocketComposer(int type,int version,int maxframesize):mType(type),mVersion(version),mMaxFrameSize(maxframesize),mDeflate(nullptr) {}
    
    int getMaxFrameSize() {return mMaxFrameSize;}

    void setMaxFrameSzie(int frame) {mMaxFrameSize = frame;}

    void setDeflate(WebSocketPermessageDeflate deflate) {mDeflate = deflate;}

    virtual ArrayList<ByteArray> genTextMessage(String) = 0;

    virtual ArrayList<ByteArray> genBinaryMessage(ByteArray) = 0;

    virtual ByteArray genPingMessage(String) = 0;

    virtual ByteArray genPongMessage(String) = 0;

    virtual ByteArray genCloseMessage(String) = 0;

protected:
    int mType;
    int mVersion;
    int mMaxFrameSize;
    WebSocketPermessageDeflate mDeflate;

    void toggleMask(ByteArray buffer, ByteArray key) const {
        byte *_out = buffer->toValue();
        byte *_key = key->toValue();
        for (size_t i = 0; i < buffer->size(); ++i) {
            _out[i] = (char)(((~ _key[i % 4])&_out[i]) | ( _key[i % 4]&(~_out[i])));
        }
    }
};

}
#endif
