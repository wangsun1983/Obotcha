#ifndef __OBOTCHA_WEB_SOCKET_HYBI13_COMPOSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI13_COMPOSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketComposer.hpp"
#include "Sha.hpp"
#include "Base64.hpp"
#include "Random.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 00
/**
 * There are many differences between Hybi 00 and Hybi 13
 */
DECLARE_SIMPLE_CLASS(WebSocketHybi13Composer) IMPLEMENTS(WebSocketComposer){
public:
    _WebSocketHybi13Composer(int,int max = MAX_WEBSOCKET_FRAME_SIZE);

    ByteArray genShakeHandMessage(WebSocketClientInfo h);
    
    ArrayList<ByteArray> genTextMessage(WebSocketClientInfo,String);

    ArrayList<ByteArray> genBinaryMessage(WebSocketClientInfo,ByteArray);

    ByteArray genPingMessage(WebSocketClientInfo,String);

    ByteArray genPongMessage(WebSocketClientInfo,String);

    ByteArray genCloseMessage(WebSocketClientInfo,String);

private:
    ByteArray _genClientShakeHandMessage(WebSocketClientInfo h);

    ByteArray _genServerShakeHandMessage(WebSocketClientInfo h);

    ArrayList<ByteArray> _genClientMessage(WebSocketClientInfo h,ByteArray,int type);
    
    ArrayList<ByteArray> _genServerMessage(WebSocketClientInfo h,ByteArray,int type);

    ByteArray _genClientControlMessage(WebSocketClientInfo h,ByteArray,int type);

    ByteArray _genServerControlMessage(WebSocketClientInfo h,ByteArray,int type);

    Sha mSha;

    Base64 mBase64;
    
    Random mRand;
};

}
#endif
