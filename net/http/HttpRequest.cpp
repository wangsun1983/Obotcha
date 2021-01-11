#include "HttpRequest.hpp"
#include "UUID.hpp"

namespace obotcha {

_HttpRequest::_HttpRequest(int m,HttpUrl url) {
    mPacket = createHttpPacket();
    mUrl = url;
    mMethod = m;
}

void _HttpRequest::setHeader(String key,String value) {
    mPacket->getHeader()->setValue(key,value);
}

void _HttpRequest::setEntity(String entity) {
    mPacket->setBody(entity);
}

void _HttpRequest::setVersion(int major,int minor) {
    mPacket->setMajorVersion(major);
    mPacket->setMinorVersion(minor);
}

void _HttpRequest::setMajorVer(int v) {
    mPacket->setMajorVersion(v);
}

void _HttpRequest::setMinorVer(int v) {
    mPacket->setMinorVersion(v);
}

void _HttpRequest::addMultiPartContent(HttpMultiPartContent content) {
    mPacket->getMultiPart()->contents->add(content);
}

void _HttpRequest::addMultiPartFile(HttpMultiPartFile file) {
    mPacket->getMultiPart()->files->add(file);
}

String _HttpRequest::getHeader(String key) {
    return mPacket->getHeader()->getValue(key);
}

String _HttpRequest::getEntity() {
    return mPacket->getBody();
}

HttpUrl _HttpRequest::getUrl() {
    return mUrl;
}

void _HttpRequest::setMethod(int method) {
    mMethod = method;
}

int _HttpRequest::getMethod() {
    return mMethod;
}


    
}

