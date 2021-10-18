#include "HttpPacketBuilder.hpp"
#include "KeyValuePair.hpp"

namespace obotcha {

_HttpPacketBuilder::_HttpPacketBuilder() { begin(); }

_HttpPacketBuilder *_HttpPacketBuilder::begin() {
    header = createHttpHeader();
    entity = createHttpEntity();
    part = createHttpMultiPart();
    method = -1;
    url = nullptr;
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::setVersion(int major, int minor) {
    header->setVersion(createHttpVersion(major, minor));
    return this;
}

_HttpPacketBuilder *
_HttpPacketBuilder::setHttpCacheControl(HttpCacheControl ctrl) {
    header->setCacheControl(ctrl);
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::setContentType(String type) {
    header->setContentType(type);
    return this;
}

// request
_HttpPacketBuilder *_HttpPacketBuilder::addCookie(HttpCookie cookie) {
    header->addCookie(cookie);
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::setContent(ByteArray c) {
    entity->setContent(c);
    return this;
}

//_HttpPacketBuilder *_HttpPacketBuilder::addEncodeValue(String key,
//                                                       String value) {
//    entity->getEncodedKeyValues()->add(
//        createKeyValuePair<String, String>(key, value));
//    return this;
//}

_HttpPacketBuilder *_HttpPacketBuilder::setMethod(int m) {
    method = m;
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::setUrl(String url) {
    this->url = createHttpUrl(url);
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::addHeaderValue(String key,
                                                       String value) {
    header->set(key, value);
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::setPort(int port) {
    if (this->url != nullptr) {
        this->url->setPort(port);
    }
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::addMultiPartFile(File file,String name) {
    HttpMultiPartFile f = createHttpMultiPartFile(file,name);
    part->files->add(f);
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::addMultiPartValue(String key,
                                                          String value) {
    part->contents->add(createKeyValuePair<String, String>(key, value));
    return this;
}

// response
_HttpPacketBuilder *_HttpPacketBuilder::setResponseStatus(int resp) {
    // status = resp;
    header->setResponseStatus(resp);
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::setResponseReason(String r) {
    // reason = r;
    header->setResponseReason(r);
    return this;
}

_HttpPacketBuilder *_HttpPacketBuilder::setChunckedFile(File f) {
    chunkedFile = f;
    return this;
}

HttpRequest _HttpPacketBuilder::newHttpReqeust() {
    HttpRequest req = createHttpRequest();
    req->getHeader()->setMethod(method);
    req->getHeader()->setUrl(url);

    req->setHeader(header);
    req->setEntity(entity);
    return createHttpRequest(req);
}

HttpResponse _HttpPacketBuilder::newHttpResponse() {
    HttpResponse resp = createHttpResponse();
    resp->setHeader(header);
    resp->setEntity(entity);

    return resp;
}

} // namespace obotcha
