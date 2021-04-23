#ifndef __OBOTCHA_HTTP_PACKET_BUILDER_HPP__
#define __OBOTCHA_HTTP_PACKET_BUILDER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "HttpMultiPart.hpp"
#include "HttpHeader.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpPacketBuilder) {

public:
    _HttpPacketBuilder();
    _HttpPacketBuilder * begin();

    _HttpPacketBuilder * setVersion(int,int);
    _HttpPacketBuilder * setHttpCacheControl(HttpCacheControl);
    _HttpPacketBuilder * setContentType(String);
    _HttpPacketBuilder * addHeaderValue(String key,String value);

    //request
    _HttpPacketBuilder * addCookie(String,String);
    _HttpPacketBuilder * setContent(ByteArray);
    _HttpPacketBuilder * addEncodeValue(String,String);
    _HttpPacketBuilder * setMethod(int);
    _HttpPacketBuilder * setUrl(String url);
    _HttpPacketBuilder * setPort(int port);
    _HttpPacketBuilder * addMultiPartFile(File);
    _HttpPacketBuilder * addMultiPartValue(String,String);

    //response
    _HttpPacketBuilder * setResponseStatus(int);
    _HttpPacketBuilder * setResponseReason(String);
    _HttpPacketBuilder * setChunckedFile(File);
    
    HttpRequest newHttpReqeust();
    HttpResponse newHttpResponse();


private:
    HttpHeader header;
    HttpEntity entity;

    //request
    int method;
    HttpUrl url;
    HttpMultiPart part;

    //response
    File chunkedFile;
    
};

}

#endif
