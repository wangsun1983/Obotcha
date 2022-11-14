#ifndef __OBOTCHA_HTTP_HEADER_ORIGIN_HPP__
#define __OBOTCHA_HTTP_HEADER_ORIGIN_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderOrigin) {

public:
    _HttpHeaderOrigin();
    _HttpHeaderOrigin(String);

    void import(String);
    
    HttpUrl get();
    void set(HttpUrl);

    String toString();

private:
    HttpUrl mUrl;
};

}
#endif
