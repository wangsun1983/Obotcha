#ifndef __OBOTCHA_WEB_HYBI13_SOCKET_VALIDATOR_HPP__
#define __OBOTCHA_WEB_HYBI13_SOCKET_VALIDATOR_HPP__

#include "Object.hpp"
#include "HttpHeader.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "WebSocketValidator.hpp"
#include "HttpResponse.hpp"
#include "Base64.hpp"
#include "Sha.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketHybi13Validator) IMPLEMENTS(WebSocketValidator) {
public:
    _WebSocketHybi13Validator();

    bool validateHandShake(HttpHeader) override;
    WebSocketPermessageDeflate validateExtensions(HttpHeader) override;
    bool validateEntirePacket(ByteArray pack) override;
    ArrayList<String> extractSubprotocols(HttpHeader) override;
    HttpResponse createServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols,WebSocketPermessageDeflate deflate) override;
    HttpRequest createClientShakeHandMessage(HttpUrl) override;

private:
    Base64 mBase64;
    Sha mSha;

};

}
#endif
