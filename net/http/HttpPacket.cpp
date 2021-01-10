#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "HttpPacket.hpp"
#include "HttpMethod.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpResponse.hpp"

namespace obotcha {

_HttpPacket::_HttpPacket() {
    mHeader = createHttpHeader();
    mMinorVer = 1;
	mMajorVer = 1;
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

ByteArray _HttpPacket::getBody() {
	return mBody;
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
    mHeader->setMethod(v);
}

int _HttpPacket::getMethod() {
    return mHeader->getMethod();
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

void _HttpPacket::setMultiPart(HttpMultiPart p) {
    mMultiPart = p;
}

HttpMultiPart _HttpPacket::getMultiPart() {
    return mMultiPart;
}

String _HttpPacket::genHttpRequest() {
    String req = createString();
    switch(mHeader->getMethod()) {
        case st(HttpMethod)::Get:
        req = createString("GET");
        break;

        case st(HttpMethod)::Post:
        req = createString("POST");
        break;

        default:
        return nullptr;
    }

    req = req->append(" ",mUrl,
                      " HTTP/",createString(mMajorVer),".",createString(mMinorVer),
                      "\r\n",
                      mHeader->toString());

    return req;   
}

ArrayList<HttpCookie> _HttpPacket::getCookies() {
    return mHeader->getCookies();
}

void _HttpPacket::addCookie(HttpCookie c) {
    mHeader->addCookie(c);
}

void _HttpPacket::dump() {
    //MapIterator<int,String> getIterator();
	MapIterator<String,String> iterator = mHeader->getIterator();
	while(iterator->hasValue()) {
		String key = iterator->getKey();
		String value = iterator->getValue();
        printf("[%s]:%s \n",key->toChars(),value->toChars());
		iterator->next();
	}

	//dump body
	if(mBody != nullptr) {
		printf("body is %s \n",mBody->toString()->toChars());
	} else {
		printf("body is null \n");
	}
}

}

