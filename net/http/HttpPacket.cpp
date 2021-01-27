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
    mVersion = createHttpVersion();
    mMultiPart = nullptr;
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
    mVersion->setMajorVer(v);
}

int _HttpPacket::getMajorVersion() {
    return mVersion->getMajorVer();
}

void _HttpPacket::setMinorVersion(int v) {
    mVersion->setMinorVer(v);
}

int _HttpPacket::getMinorVersion() {
    return mVersion->getMinorVer();
}

HttpVersion _HttpPacket::getVersion() {
    return mVersion;
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

HashMap<String,String> _HttpPacket::getEncodedKeyValues() {
    return mFormUrlEncodedMap;
}

String _HttpPacket::getEncodedKeyValue(String key) {
    if(mFormUrlEncodedMap != nullptr) {
        return mFormUrlEncodedMap->get(key);
    }
    
    return nullptr;
}

void _HttpPacket::setEncodedKeyValues(HashMap<String,String> map) {
    mFormUrlEncodedMap = map;
}

void _HttpPacket::addEncodedKeyValue(String key,String value) {
    if(mFormUrlEncodedMap == nullptr) {
        mFormUrlEncodedMap = createHashMap<String,String>();
    }
    mFormUrlEncodedMap->put(key,value);
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

    ArrayList<HttpCookie> cookies = mHeader->getCookies();
    if(cookies != nullptr) {
        ListIterator<HttpCookie> iterator2 = cookies->getIterator();
        printf("start iterator2 \n");
        while(iterator2->hasValue()) {
            HttpCookie cookie = iterator2->getValue();
            cookie->dump();
            iterator2->next();
        }
        printf("start iterator3 \n");
    }

	//dump body
	if(mBody != nullptr) {
		printf("body is %s \n",mBody->toString()->toChars());
	} else {
		printf("body is null \n");
	}
}

}

