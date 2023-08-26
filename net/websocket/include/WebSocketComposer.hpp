#ifndef __OBOTCHA_WEB_SOCKET_COMPOSER_HPP__
#define __OBOTCHA_WEB_SOCKET_COMPOSER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "WebSocketProtocol.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketComposer) {
public:
    static const int kMaxWebSocketFrameSize = 64*1024;

    _WebSocketComposer(_WebSocketProtocol::Model model,int version,int maxframesize):mModel(model),mVersion(version),mMaxFrameSize(maxframesize) {}
    
    int getMaxFrameSize() const {
        return mMaxFrameSize;
    }

    void setMaxFrameSzie(int frame) {
        mMaxFrameSize = frame;
    }

    void setDeflate(WebSocketPermessageDeflate deflate) {
        mDeflate = deflate;
    }

    virtual ArrayList<ByteArray> genTextMessage(String) = 0;

    virtual ArrayList<ByteArray> genBinaryMessage(ByteArray) = 0;

    virtual ByteArray genPingMessage(String) = 0;

    virtual ByteArray genPongMessage(String) = 0;

    virtual ByteArray genCloseMessage(String) = 0;

protected:
    _WebSocketProtocol::Model mModel;
    int mVersion;
    int mMaxFrameSize;
    WebSocketPermessageDeflate mDeflate = nullptr;

    void toggleMask(ByteArray buffer, ByteArray key) const {
        byte *_out = buffer->toValue();
        const byte *_key = key->toValue();
        for (size_t i = 0; i < buffer->size(); ++i) {
            _out[i] = (char)(((~ _key[i % 4])&_out[i]) | ( _key[i % 4]&(~_out[i])));
        }
    }
};

}
#endif
