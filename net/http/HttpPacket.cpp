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
    mEntity = createHttpEntity();
}

void _HttpPacket::setHeader(HttpHeader h) {
    mHeader = h;
}

HttpHeader _HttpPacket::getHeader() {
    return mHeader;
}

HttpEntity _HttpPacket::getEntity() {
    return mEntity;   
}
    
void _HttpPacket::setEntity(HttpEntity entity) {
    mEntity = entity;
}
    
void _HttpPacket::setUrl(String url) {
    mUrl = url;
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

HttpVersion _HttpPacket::getVersion() {
    return mVersion;
}

void _HttpPacket::setVersion(HttpVersion h) {
    mVersion = h;
}

int _HttpPacket::getStatus() {
    return mStatusCode;
}

void _HttpPacket::setStatus(int v) {
    mStatusCode = v;
}

void _HttpPacket::dump() {
#if 0    
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
#endif
}

}

