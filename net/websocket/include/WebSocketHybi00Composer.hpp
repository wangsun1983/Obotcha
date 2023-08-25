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
    explicit _WebSocketHybi00Composer(_WebSocketProtocol::Model model,int ver = 0,int max = kMaxWebSocketFrameSize);
    
    HttpRequest genClientShakeHandMessage(HttpUrl);

    HttpResponse genServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols);
    
    ArrayList<ByteArray> genTextMessage(String) override;
    
    ArrayList<ByteArray> genBinaryMessage(ByteArray) override;

    ByteArray genPingMessage(String) override;

    ByteArray genPongMessage(String) override;

    ByteArray genCloseMessage(String) override;

    ByteArray generateControlFrame(int opcode, ByteArray payload);

};

}
#endif
