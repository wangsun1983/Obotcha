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
    bool validateHandShake(HttpHeader);
    WebSocketPermessageDeflate validateExtensions(HttpHeader);
    bool validateEntirePacket(ByteArray pack);
    ArrayList<String> extractSubprotocols(HttpHeader);
    HttpResponse createServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols,WebSocketPermessageDeflate);
    HttpRequest createClientShakeHandMessage(HttpUrl);
};

}
#endif
