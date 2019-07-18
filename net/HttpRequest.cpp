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

void _HttpRequest::insertHeader(String,String) {

}

void _HttpRequest::setHeader(HttpHeader h) {
    mHeader = h;
}

HttpHeader _HttpRequest::getHeader(HttpHeader) {
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

}

