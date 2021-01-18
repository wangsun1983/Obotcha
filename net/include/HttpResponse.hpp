#ifndef __OBOTCHA_HTTP_RESPONSE_HPP__
#define __OBOTCHA_HTTP_RESPONSE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

class _HttpResponseWriter;

DECLARE_SIMPLE_CLASS(HttpResponse) {
public:
    friend class _HttpResponseWriter;
    _HttpResponse(HttpPacket packet);
	
	_HttpResponse();

    int getStatus();
	void setStatus(int);
	
	void setBody(ByteArray);
	ByteArray getBody();

	void setHeader(String,String);
	String getHeader(String);
	HttpHeader getHeaders();

	void setFile(File);
	File getFile();
	void addCookie(HttpCookie);

	void dump();

private:
	HttpPacket mPacket;
	File mFile;
};

}
#endif
