#include "HttpRequest.hpp"
#include "UUID.hpp"

namespace obotcha {

_HttpRequest::_HttpRequest(int,HttpUrl url) {
    mPacket = createHttpPacket();
    mUrl = url;
    mMajorVersion = 1;
    mMinorVersion = 1;
}

void _HttpRequest::setHeader(String key,String value) {
    mPacket->getHeader()->setValue(key,value);
}

void _HttpRequest::setEntity(String entity) {
    mPacket->setBody(entity);
}

void _HttpRequest::setVersion(int major,int minor) {
    mMajorVersion = major;
    mMinorVersion = minor;
}

int _HttpRequest::getMajorVersion() {
    return mMajorVersion;
}

int _HttpRequest::getMinorVersion() {
    return mMinorVersion;
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

