#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpHeader.hpp"
#include "HttpMethod.hpp"
#include "HttpPacket.hpp"
#include "HttpResponse.hpp"
#include "String.hpp"

namespace obotcha {

_HttpPacket::_HttpPacket() {
    mHeader = createHttpHeader();
    mEntity = createHttpEntity();
}

void _HttpPacket::setHeader(HttpHeader h) { mHeader = h; }

HttpHeader _HttpPacket::getHeader() { return mHeader; }

HttpEntity _HttpPacket::getEntity() { return mEntity; }

void _HttpPacket::setEntity(HttpEntity entity) { mEntity = entity; }

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

} // namespace obotcha
