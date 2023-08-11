#ifndef __OBOTCHA_WEB_HYBI00_SOCKET_VALIDATOR_HPP__
#define __OBOTCHA_WEB_HYBI00_SOCKET_VALIDATOR_HPP__

#include "Object.hpp"
#include "HttpHeader.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "WebSocketValidator.hpp"
#include "HttpResponse.hpp"
#include "Base64.hpp"
#include "Sha.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketHybi00Validator) IMPLEMENTS(WebSocketValidator){
public:
    bool validateHandShake(HttpHeader) override;
    WebSocketPermessageDeflate validateExtensions(HttpHeader) override;
    bool validateEntirePacket(ByteArray pack) override;
    ArrayList<String> extractSubprotocols(HttpHeader) override;
    HttpResponse createServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols,WebSocketPermessageDeflate) override;
    HttpRequest createClientShakeHandMessage(HttpUrl) override;
};

}
#endif
