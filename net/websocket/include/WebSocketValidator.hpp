#ifndef __OBOTCHA_WEB_SOCKET_VALIDATOR_HPP__
#define __OBOTCHA_WEB_SOCKET_VALIDATOR_HPP__

#include "Object.hpp"
#include "HttpHeader.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "Base64.hpp"
#include "Sha.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketValidator) {

public:
    virtual bool validateHandShake(HttpHeader) = 0;
    virtual WebSocketPermessageDeflate validateExtensions(HttpHeader) = 0;
    virtual bool validateEntirePacket(ByteArray pack) = 0;
    virtual ArrayList<String> extractSubprotocols(HttpHeader) = 0;
    virtual HttpResponse createServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols,WebSocketPermessageDeflate deflate) = 0;
    virtual HttpRequest createClientShakeHandMessage(HttpUrl) = 0;

};

}
#endif
