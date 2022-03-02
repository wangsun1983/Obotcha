#ifndef __OBOTCHA_HTTP_DELETE_HPP__
#define __OBOTCHA_HTTP_DELETE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpRequest.hpp"
#include "HttpClientBaseRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpDelete) IMPLEMENTS(HttpClientBaseRequest){
public:
    _HttpDelete(String);

    String getMethodName();

private:
    HttpUrl mUrl;
};

}

#endif