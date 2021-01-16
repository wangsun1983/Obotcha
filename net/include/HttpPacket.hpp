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
#include "HttpMultiPart.hpp"
#include "HttpVersion.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpPacket) {

public:

    friend class _HttpRequestParser;
    friend class _HttpResponseParser;

    _HttpPacket();
    
    void setHeader(HttpHeader);
    
    HttpHeader getHeader();

    void setBody(ByteArray);

    ByteArray getBody();
    
    void setUrl(String);
    
    String getUrl();

    void setReason(String);
    
    String getReason();

    void setMethod(int);

    int getMethod();

    void setMajorVersion(int);

    int getMajorVersion();

    void setMinorVersion(int);

    int getMinorVersion();

    HttpVersion getVersion();

    int getStatusCode();

    void setStatusCode(int);

    void setMultiPart(HttpMultiPart);

    HttpMultiPart getMultiPart();

    ArrayList<HttpCookie> getCookies();

    void addCookie(HttpCookie);

    HashMap<String,String> getEncodedKeyValues();

    String getEncodedKeyValue(String);

    void setEncodedKeyValues(HashMap<String,String>);
    
    void addEncodedKeyValue(String,String);

    void dump();

private:
    String mUrl;
    
    HttpHeader mHeader;

    ByteArray mBody;

    String mReason;

    HttpVersion mVersion;

    int mStatusCode;

    //support for httpparse
    String tempParseValue;

    String tempParseField;

    HttpMultiPart mMultiPart;

    HashMap<String,String>mFormUrlEncodedMap;

};

}
#endif
