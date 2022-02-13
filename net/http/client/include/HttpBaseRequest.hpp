#ifndef __OBOTCHA_HTTP_GET_HPP__
#define __OBOTCHA_HTTP_GET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRequest.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpBaseRequest) IMPLEMENTS(HttpRequest){
public:
    void setUrl(HttpUrl);
    void setUrl(String);
    HttpUrl getUrl();

private:
    HttpUrl mUrl;
};

}

#endif