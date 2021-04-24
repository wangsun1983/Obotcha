#ifndef __OBOTCHA_HTTP_REQUEST_HPP__
#define __OBOTCHA_HTTP_REQUEST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "HttpMultiPart.hpp"
#include "HttpHeader.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRequest) IMPLEMENTS(HttpPacket){

public:
    friend class _HttpRequestWriter;
    _HttpRequest(int,HttpUrl);
    _HttpRequest();

    String toString();
    
};

}

#endif
