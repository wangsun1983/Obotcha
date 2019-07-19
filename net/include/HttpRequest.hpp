#ifndef __HTTP_REQUEST_HPP__
#define __HTTP_REQUEST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRequest) {

public:
    _HttpRequest();
    
    void setHeader(HttpHeader);
    
    HttpHeader getHeader();

    void setBody(ByteArray);
    
    void setUrl(String);
    
    String getUrl();

    void setReason(String);
    
    String getReason();

private:
    String mUrl;
    HttpHeader mHeader;
    ByteArray mBody;
    String mReason;

    

};

}
#endif
