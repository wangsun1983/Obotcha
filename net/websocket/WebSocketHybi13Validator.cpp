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
    Inspect(h->getMethod() != st(HttpMethod)::Get || h->getWebSocketKey() == nullptr,
            false);
    return true;
}

WebSocketPermessageDeflate _WebSocketHybi13Validator::validateExtensions(HttpHeader h) {
    auto ext = h->getWebSocketExtensions();
    Inspect(ext == nullptr,nullptr);

    auto deflate = createWebSocketPermessageDeflate();
    Inspect(deflate->fit(ext->get()),deflate);

    return nullptr;
}

bool _WebSocketHybi13Validator::validateEntirePacket(ByteArray pack) {
    return true;
}

ArrayList<String> _WebSocketHybi13Validator::extractSubprotocols(HttpHeader h) {
    ArrayList<String> protocols = createArrayList<String>();
    auto protocol = h->getWebSocketProtocol();
    Inspect(protocol == nullptr,nullptr);
    return protocol->get();
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
    header->setMethod(st(HttpMethod)::Get);
    //packet->setHeader(client->getHttpHeader());
    header->setUrl(httpUrl);
    header->setVersion(createHttpHeaderVersion(1,1));

    String host = httpUrl->getHost()->append(":",createString(httpUrl->getPort()));
    header->set(st(HttpHeader)::Host,host);
    header->set(st(HttpHeader)::SecWebSocketVersion,createString("13"));
    //if(header->get(st(HttpHeader)::Accept) == nullptr) {
    if(header->getAccept() == nullptr) {
        header->set(st(HttpHeader)::Accept,createString("*/*"));
    }

    //if(header->get(st(HttpHeader)::AcceptLanguage) == nullptr) {
    if(header->getAcceptLanguage() == nullptr) {
        header->set(st(HttpHeader)::AcceptLanguage,createString("en-US,en;q=0.5"));
    }

    //if(header->getAcceptEncoding() == nullptr) {
    if(header->getAcceptEncoding() == nullptr) {
        header->set(st(HttpHeader)::AcceptEncoding,createString("gzip, deflate"));
    }

    //if(header->get(st(HttpHeader)::Origin) == nullptr) {
    //if(header->getOrigin() == nullptr) {
    //    header->set(st(HttpHeader)::Origin,createString("null"));
    //}

    //if(header->get(st(HttpHeader)::SecWebSocketKey) == nullptr) {
    if(header->getWebSocketKey() == nullptr) {
        //we should gen a sec key
        Random rand = createRandom();
        ByteArray array = createByteArray(16);
        rand->nextBytes(array);
        Base64 base64key = createBase64();
        ByteArray key = base64key->encode(array);
        header->set(st(HttpHeader)::SecWebSocketKey,key->toString());
    }

    //if(header->get(st(HttpHeader)::Connection) == nullptr) {
    if(header->getConnection() == nullptr) {
        header->set(st(HttpHeader)::Connection,createString("keep-alive, Upgrade"));
    }

    //if(header->get(st(HttpHeader)::Upgrade) == nullptr) {
    if(header->getUpgrade() == nullptr) {
        header->set(st(HttpHeader)::Upgrade,createString("websocket"));
    }

    if(header->get(st(HttpHeader)::Pragma) == nullptr) {
        header->set(st(HttpHeader)::Pragma,createString("no-cache"));
    }

    //if(header->get(st(HttpHeader)::CacheControl) == nullptr) {
    if(header->getCacheControl() == nullptr) {
        header->set(st(HttpHeader)::CacheControl,createString("no-cache"));
    }

    return packet;
}

}
