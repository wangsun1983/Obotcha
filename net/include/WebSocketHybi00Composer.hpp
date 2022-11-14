#ifndef __OBOTCHA_WEB_SOCKET_HYBI00_COMPOSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI00_COMPOSER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "HttpHeader.hpp"
#include "WebSocketComposer.hpp"
#include "HttpRequest.hpp"

namespace obotcha {


DECLARE_CLASS(WebSocketHybi00Composer) IMPLEMENTS(WebSocketComposer) {
public:
    _WebSocketHybi00Composer(int type,int ver = 0,int max = MAX_WEBSOCKET_FRAME_SIZE);
    
    HttpRequest genClientShakeHandMessage(HttpUrl);

    HttpResponse genServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols);
    
    ArrayList<ByteArray> genTextMessage(String);
    
    ArrayList<ByteArray> genBinaryMessage(ByteArray);

    ByteArray genPingMessage(String);

    ByteArray genPongMessage(String);

    ByteArray genCloseMessage(String);

    ByteArray generateControlFrame(int opcode, ByteArray payload);

};

}
#endif
