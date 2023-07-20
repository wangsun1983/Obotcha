#ifndef __OBOTCHA_HTTP_POST_HPP__
#define __OBOTCHA_HTTP_POST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRequest.hpp"
#include "HttpClientBaseRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPost) IMPLEMENTS(HttpClientBaseRequest){
public:
    explicit _HttpPost(String);

    String getMethodName();
};

}

#endif