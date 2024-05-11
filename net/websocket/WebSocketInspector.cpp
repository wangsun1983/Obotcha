#include "WebSocketInspector.hpp"
#include "WebSocketHybi00Validator.hpp"
#include "WebSocketHybi07Validator.hpp"
#include "WebSocketHybi08Validator.hpp"
#include "WebSocketHybi13Validator.hpp"
#include "Log.hpp"

namespace obotcha {

_WebSocketInspector::_WebSocketInspector(int version) {
    switch (version) {
        case 0: {
            mValidator = WebSocketHybi00Validator::New();
            break;
        }

        case 7: {
            mValidator = WebSocketHybi07Validator::New();
            break;
        }

        case 8: {
            mValidator = WebSocketHybi08Validator::New();
            break;
        }

        case 13: {
            mValidator = WebSocketHybi13Validator::New();
            break;
        }

        default:
            LOG(ERROR)<<"WebSocket OutputWriter Protocol Not Support,Version is "<<version;
        break;
    }
}

bool _WebSocketInspector::validateHandShake(HttpHeader h) {
    return mValidator->validateHandShake(h);
}

WebSocketPermessageDeflate _WebSocketInspector::validateExtensions(HttpHeader h) {
    return mValidator->validateExtensions(h);
}

bool _WebSocketInspector::validateEntirePacket(ByteArray pack) {
    return mValidator->validateEntirePacket(pack);
}

ArrayList<String> _WebSocketInspector::extractSubprotocols(HttpHeader h) {
    return mValidator->extractSubprotocols(h);
}

HttpResponse _WebSocketInspector::createServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols,WebSocketPermessageDeflate deflate) {
    return mValidator->createServerShakeHandMessage(SecWebSocketKey,protocols,deflate);
}

HttpRequest _WebSocketInspector::createClientShakeHandMessage(HttpUrl h) {
    return mValidator->createClientShakeHandMessage(h);
}


}
