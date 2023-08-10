#ifndef __OBOTCHA_HTTP_GET_HPP__
#define __OBOTCHA_HTTP_GET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRequest.hpp"
#include "HttpClientBaseRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpGet) IMPLEMENTS(HttpClientBaseRequest){
public:
    explicit _HttpGet(String);

    String getMethodName() const;
};

}

#endif