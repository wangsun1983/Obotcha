#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "HttpRequest.hpp"

namespace obotcha {

_HttpRequest::_HttpRequest() {
    mHeader = createHttpHeader();
}

void _HttpRequest::setHeader(HttpHeader h) {
    mHeader = h;
}

HttpHeader _HttpRequest::getHeader() {
    return mHeader;
}
    
void _HttpRequest::setUrl(String url) {
    mUrl = url;
}

void _HttpRequest::setBody(ByteArray body) {
    mBody = body;
}

String _HttpRequest::getUrl() {
    return mUrl;
}

void _HttpRequest::setReason(String reason) {
    mReason = reason;
}

String _HttpRequest::getReason() {
    return mReason;
}

void _HttpRequest::setMethod(int v) {
    mMethod = v;
}

int _HttpRequest::getMethod() {
    return mMethod;
}

void _HttpRequest::setMajorVersion(int v) {
    mMajorVer = v;
}

int _HttpRequest::getMajorVersion() {
    return mMajorVer;
}

void _HttpRequest::setMinorVersion(int v) {
    mMinorVer = v;
}

int _HttpRequest::getMinorVersion() {
    return mMinorVer;
}

String _HttpRequest::genHttpString() {
    String req = createString();
    switch(mMethod) {
        case HttpMethodGet:
        req = createString("GET");
        break;

        case HttpMethodPost:
        req = createString("POST");
        break;

        default:
        return nullptr;
    }

    req = req->append(" ")
             ->append(mUrl)
             ->append(" HTTP/")
             ->append(createString(mMajorVer))
             ->append(".")
             ->append(createString(mMinorVer))
             ->append("\r\n");

    //conver header
    MapIterator<Integer,String> headerIte = mHeader->getIterator();
    while(headerIte->hasValue()) {
        String headSting = st(HttpHeader)::getHeaderString(headerIte->getKey()->toValue());
        req = req->append(headSting)
                 ->append(": ")
                 ->append(headerIte->getValue())
                 ->append("\r\n");
        headerIte->next();
    }

    req = req->append("\r\n\r\n");

    return req;   
}

}

