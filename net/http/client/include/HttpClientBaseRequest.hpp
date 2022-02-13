#ifndef __OBOTCHA_HTTP_CLIENT_BASE_REQUESET_HPP__
#define __OBOTCHA_HTTP_CLIENT_BASE_REQUESET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRequest.hpp"
#include "URL.hpp"

namespace obotcha {

DECLARE_CLASS(HttpClientBaseRequest) IMPLEMENTS(HttpRequest){
public:
    _HttpClientBaseRequest(String);
    HttpUrl getUrl();

private:
    HttpUrl mUrl;
};

}

#endif