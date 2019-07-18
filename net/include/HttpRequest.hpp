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

    void insertHeader(String,String);
    
    void setHeader(HttpHeader);
    
    HttpHeader getHeader(HttpHeader);

    void setBody(ByteArray);
    
    void setUrl(String);
    
    String getUrl();

private:
    String mUrl;
    HttpHeader mHeader;
    ByteArray mBody;

    

};

}
#endif
