#ifndef __OBOTCHA_HTTP_PUT_HPP__
#define __OBOTCHA_HTTP_PUT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRequest.hpp"
#include "HttpClientBaseRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPut) IMPLEMENTS(HttpClientBaseRequest){
public:
    explicit _HttpPut(String);

    String getMethodName();
};

}

#endif