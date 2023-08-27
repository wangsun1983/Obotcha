#include "WebSocketHybi13Validator.hpp"
#include "HttpMethod.hpp"
#include "HttpStatus.hpp"
#include "Inspect.hpp"
#include "WebSocketProtocol.hpp"
#include "Random.hpp"

namespace obotcha {

_WebSocketHybi13Validator::_WebSocketHybi13Validator() {
    mBase64 = createBase64();
    mSha = createSha(SHA_1);
}

bool _WebSocketHybi13Validator::validateHandShake(HttpHeader h) {
    return h->getMethod() == st(HttpMethod)::Id::Get && h->getWebSocketKey() != nullptr;
}

WebSocketPermessageDeflate _WebSocketHybi13Validator::validateExtensions(HttpHeader h) {
    auto ext = h->getWebSocketExtensions();
    Inspect(ext == nullptr,nullptr)

    auto deflate = createWebSocketPermessageDeflate();
    return deflate->fit(ext->get())?deflate:nullptr;
}

bool _WebSocketHybi13Validator::validateEntirePacket(ByteArray pack) {
    //TODO
    return true;
}

ArrayList<String> _WebSocketHybi13Validator::extractSubprotocols(HttpHeader h) {
    auto protocol = h->getWebSocketProtocol();
    return (protocol == nullptr)?nullptr:protocol->get();
}

HttpResponse _WebSocketHybi13Validator::createServerShakeHandMessage(String SecWebSocketKey,ArrayList<String> protocols,WebSocketPermessageDeflate deflate) {
    String key = SecWebSocketKey;
    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    ByteArray sha1_content = mSha->encryptRawData(key_mgic->toByteArray());
    String base64 = mBase64->encode(sha1_content)->toString();

    HttpResponse response = createHttpResponse();
    response->getHeader()->setResponseReason(st(HttpStatus)::toString(st(HttpStatus)::SwitchProtocls));
    response->getHeader()->setResponseStatus(st(HttpStatus)::SwitchProtocls);
    response->getHeader()->set(st(HttpHeader)::SecWebSocketAccept,base64);
    response->getHeader()->setUpgrade(createString("websocket"));
    response->getHeader()->setConnection(createString("Upgrade"));

    if(protocols != nullptr) {
        HttpHeaderSecWebSocketProtocol protocol = createHttpHeaderSecWebSocketProtocol();
        protocol->set(protocols);
        response->getHeader()->setWebSocketProtocol(protocol);
    }

    if(deflate != nullptr) {
        String extension = createString("permessage-deflate")->append(";client_max_window_bits=",
                            createString(deflate->getServerMaxWindowBits()));

        response->getHeader()->set(st(HttpHeader)::SecWebSocketExtensions,extension);
    }

    return response;
}

HttpRequest _WebSocketHybi13Validator::createClientShakeHandMessage(HttpUrl httpUrl) {
    HttpRequest packet = createHttpRequest();
    auto header = packet->getHeader();
    header->setMethod(st(HttpMethod)::Id::Get);
    header->setUrl(httpUrl);
    header->setVersion(createHttpHeaderVersion(1,1));

    String host = httpUrl->getHost()->append(":",createString(httpUrl->getPort()));
    header->set(st(HttpHeader)::Host,host);
    header->set(st(HttpHeader)::SecWebSocketVersion,createString("13"));
    if(header->getAccept() == nullptr) {
        header->set(st(HttpHeader)::Accept,createString("*/*"));
    }

    if(header->getAcceptLanguage() == nullptr) {
        header->set(st(HttpHeader)::AcceptLanguage,createString("en-US,en;q=0.5"));
    }

    if(header->getAcceptEncoding() == nullptr) {
        header->set(st(HttpHeader)::AcceptEncoding,createString("gzip, deflate"));
    }

    if(header->getWebSocketKey() == nullptr) {
        //we should gen a sec key
        Random rand = createRandom();
        ByteArray array = createByteArray(16);
        rand->nextBytes(array);
        Base64 base64key = createBase64();
        ByteArray key = base64key->encode(array);
        header->set(st(HttpHeader)::SecWebSocketKey,key->toString());
    }

    if(header->getConnection() == nullptr) {
        header->set(st(HttpHeader)::Connection,createString("keep-alive, Upgrade"));
    }

    if(header->getUpgrade() == nullptr) {
        header->set(st(HttpHeader)::Upgrade,createString("websocket"));
    }

    if(header->getPragma() == nullptr) {
        header->set(st(HttpHeader)::Pragma,createString("no-cache"));
    }

    if(header->getCacheControl() == nullptr) {
        header->set(st(HttpHeader)::CacheControl,createString("no-cache"));
    }

    return packet;
}

}
