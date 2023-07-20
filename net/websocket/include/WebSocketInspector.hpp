#ifndef __OBOTCHA_WEB_SOCKET_INSPECTOR_HPP__
#define __OBOTCHA_WEB_SOCKET_INSPECTOR_HPP__

#include "Object.hpp"
#include "WebSocketValidator.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketInspector) {

public:
    explicit _WebSocketInspector(int version);

    bool validateHandShake(HttpHeader);
    WebSocketPermessageDeflate validateExtensions(HttpHeader);
    bool validateEntirePacket(ByteArray pack);
    ArrayList<String> extractSubprotocols(HttpHeader);
    HttpResponse createServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols,WebSocketPermessageDeflate deflate);
    HttpRequest createClientShakeHandMessage(HttpUrl);

private:
    WebSocketValidator mValidator;

};

}
#endif
