#ifndef __OBOTCHA_HTTP_PUT_HPP__
#define __OBOTCHA_HTTP_PUT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRequest.hpp"
#include "URL.hpp"
#include "HttpClientBaseRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPut) IMPLEMENTS(HttpClientBaseRequest){
public:
    _HttpPut(String);

    String getMethodName();

private:
    HttpUrl mUrl;
};

}

#endif