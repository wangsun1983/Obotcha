#include "HttpPacketBuilder.hpp"
#include "KeyValuePair.hpp"
#include "HttpUrlParser.hpp"

namespace obotcha {

_HttpPacketBuilder::_HttpPacketBuilder() {
    
}

_HttpPacketBuilder * _HttpPacketBuilder::begin() {
    header = createHttpHeader();
    entity = createHttpEntity();
    part = createHttpMultiPart();
    method = -1;
    status = -1;
    url = nullptr;
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setVersion(int major,int minor) {
    header->setVersion(createHttpVersion(major,minor));
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setHttpCacheControl(HttpCacheControl ctrl) {
    header->setCacheControl(ctrl);
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setContentType(String type) {
    header->setContentType(type);
    return this;
}

//request
_HttpPacketBuilder * _HttpPacketBuilder::addCookie(String key,String value) {
    HttpCookie cookie = createHttpCookie();
    cookie->setValue(key,value);
    header->addCookie(cookie);
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setContent(ByteArray c) {
    entity->setContent(c);
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::addEncodeValue(String key,String value) {
    entity->getEncodedKeyValues()->add(createKeyValuePair<String,String>(key,value));
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setMethod(int m) {
    method = m;
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setUrl(String url) {
    this->url = st(HttpUrlParser)::parseUrl(url);
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setPort(int port) {
    if(this->url != nullptr) {
        this->url->setPort(port);
    }
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::addMultiPartFile(File file) {
    part->files->add(createHttpMultiPartFile(file));
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::addMultiPartValue(String key,String value) {
    part->contents->add(createKeyValuePair<String,String>(key,value));
    return this;
}

//response
_HttpPacketBuilder * _HttpPacketBuilder::setResponseStatus(int resp) {
    status = resp;
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setResponseReason(String r) {
    reason = r;
    return this;
}

_HttpPacketBuilder * _HttpPacketBuilder::setChunckedFile(File f) {
    chunkedFile = f;
}

HttpRequest _HttpPacketBuilder::newHttpReqeust() {
    HttpRequest req = createHttpRequest(method,url);
    req->setHeader(header);
    req->setEntity(entity);
    return req;

}

HttpResponse _HttpPacketBuilder::newHttpResponse() {
    HttpResponse resp = createHttpResponse();
    resp->setHeader(header);
    resp->setEntity(entity);

    return nullptr;
}

}
