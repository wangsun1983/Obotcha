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
#include "HttpResponse.hpp"
#include "HttpMultiPart.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpPacket) {

public:

    friend class _HttpV1Parser;
    
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

    int getStatusCode();

    void setStatusCode(int);

    void setMultiPart(HttpMultiPart);

    HttpMultiPart getMultiPart();

    String genHttpRequest();

    ByteArray genHttpResponse();

    ArrayList<HttpCookie> getCookies();

    void dump();

private:
    String mUrl;
    
    HttpHeader mHeader;
    
    ArrayList<HttpCookie> mCookies;

    ByteArray mBody;

    String mReason;

    //int mMethod;

    int mMajorVer;

    int mMinorVer;

    int mStatusCode;

    //support for httpv1parse
    String tempParseValue;

    String tempParseField;

    HttpMultiPart mMultiPart;

};

}
#endif
