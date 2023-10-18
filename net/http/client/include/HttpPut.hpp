#ifndef __OBOTCHA_HTTP_PUT_HPP__
#define __OBOTCHA_HTTP_PUT_HPP__

#include "Object.hpp"
#include "HttpRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPut) IMPLEMENTS(HttpRequest){
public:
    explicit _HttpPut(String url);

    String getMethodName() const;
};

}

#endif