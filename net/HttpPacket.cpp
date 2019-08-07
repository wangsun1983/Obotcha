#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

_HttpPacket::_HttpPacket() {
    mHeader = createHttpHeader();
}

void _HttpPacket::setHeader(HttpHeader h) {
    mHeader = h;
}

HttpHeader _HttpPacket::getHeader() {
    return mHeader;
}
    
void _HttpPacket::setUrl(String url) {
    mUrl = url;
}

void _HttpPacket::setBody(ByteArray body) {
    mBody = body;
}

String _HttpPacket::getUrl() {
    return mUrl;
}

void _HttpPacket::setReason(String reason) {
    mReason = reason;
}

String _HttpPacket::getReason() {
    return mReason;
}

void _HttpPacket::setMethod(int v) {
    mMethod = v;
}

int _HttpPacket::getMethod() {
    return mMethod;
}

void _HttpPacket::setMajorVersion(int v) {
    mMajorVer = v;
}

int _HttpPacket::getMajorVersion() {
    return mMajorVer;
}

void _HttpPacket::setMinorVersion(int v) {
    mMinorVer = v;
}

int _HttpPacket::getMinorVersion() {
    return mMinorVer;
}

int _HttpPacket::getStatusCode() {
    return mStatusCode;
}

void _HttpPacket::setStatusCode(int v) {
    mStatusCode = v;
}

String _HttpPacket::genHttpString() {
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

    req = req->append(mHeader->genHtml());

    req = req->append("\r\n\r\n");

    return req;   
}

}

