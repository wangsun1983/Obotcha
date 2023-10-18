#ifndef __OBOTCHA_HTTP_GET_HPP__
#define __OBOTCHA_HTTP_GET_HPP__

#include "Object.hpp"
#include "HttpRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpGet) IMPLEMENTS(HttpRequest) {
public:
    explicit _HttpGet(String url);

    String getMethodName() const;
};

}

#endif