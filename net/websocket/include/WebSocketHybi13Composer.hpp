#ifndef __OBOTCHA_WEB_SOCKET_HYBI13_COMPOSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI13_COMPOSER_HPP__

#include "Object.hpp"
#include "WebSocketComposer.hpp"
#include "Sha.hpp"
#include "Base64.hpp"
#include "Random.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 00
/**
 * There are many differences between Hybi 00 and Hybi 13
 */
DECLARE_CLASS(WebSocketHybi13Composer) IMPLEMENTS(WebSocketComposer){
public:
    explicit _WebSocketHybi13Composer(int type,int ver = 13,int max = kMaxWebSocketFrameSize);
    
    ArrayList<ByteArray> genTextMessage(String) override;

    ArrayList<ByteArray> genBinaryMessage(ByteArray) override;

    ByteArray genPingMessage(String) override;

    ByteArray genPongMessage(String) override;

    ByteArray genCloseMessage(String) override;

    ByteArray generateControlFrame(int opcode, ByteArray payload);

private:

    ArrayList<ByteArray> genClientMessage(ByteArray,int type);
    
    ArrayList<ByteArray> genServerMessage(ByteArray,int type);

    ByteArray genClientControlMessage(ByteArray,int type);

    ByteArray genServerControlMessage(ByteArray,int type);

    Sha mSha;

    Base64 mBase64;
    
    Random mRand;
};

}
#endif
