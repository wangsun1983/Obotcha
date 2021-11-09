#ifndef __OBOTCHA_HTTP_HEADER_REFERER_HPP__
#define __OBOTCHA_HTTP_HEADER_REFERER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderReferer) {

public:
    _HttpHeaderReferer();
    _HttpHeaderReferer(String);

    void import(String);
    
    HttpUrl get();
    void set(HttpUrl);

    String toString();

private:
    HttpUrl mUrl;
};

}
#endif
