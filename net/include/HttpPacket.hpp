#ifndef __OBOTCHA_HTTP_PACKET_HPP__
#define __OBOTCHA_HTTP_PACKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"

#include "HttpMethod.hpp"
#include "HttpVersion.hpp"
#include "HttpEntity.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpPacket) {

public:

    friend class _HttpRequestParser;
    friend class _HttpResponseParser;

    _HttpPacket();
    
    void setHeader(HttpHeader);
    
    HttpHeader getHeader();

    HttpEntity getEntity();

    void setEntity(HttpEntity);

    void setUrl(String);
    
    String getUrl();

    void setReason(String);
    
    String getReason();

    void setMethod(int);

    int getMethod();

    HttpVersion getVersion();

    void setVersion(HttpVersion);

    int getStatus();

    void setStatus(int);

    void dump();

private:
    String mUrl;
    
    HttpHeader mHeader;

    HttpEntity mEntity;

    String mReason;

    HttpVersion mVersion;

    int mStatusCode;

    //support for httpparse
    String tempParseValue;

    String tempParseField;
};

}
#endif
