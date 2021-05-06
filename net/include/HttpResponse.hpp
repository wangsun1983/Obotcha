#ifndef __OBOTCHA_HTTP_RESPONSE_HPP__
#define __OBOTCHA_HTTP_RESPONSE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

class _HttpResponseWriter;

DECLARE_SIMPLE_CLASS(HttpResponse) IMPLEMENTS(HttpPacket) {
public:
	enum HttpFileTransferType {
		CHUNCKED = 0,
		NORMAL
	};
    friend class _HttpResponseWriter;
    _HttpResponse();
	_HttpResponse(HttpPacket);
	
	//void setChunkedFile(File);
	//File getChunkedFile();
	void setFile(File file,int type = CHUNCKED);
	File getFile();
	int getType();
	
	String toString();

private:
	File mFile;
	int mType;
};

}
#endif
