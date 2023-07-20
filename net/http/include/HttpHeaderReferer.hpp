#ifndef __OBOTCHA_HTTP_HEADER_REFERER_HPP__
#define __OBOTCHA_HTTP_HEADER_REFERER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderReferer) {

public:
    _HttpHeaderReferer();
    explicit _HttpHeaderReferer(String);

    void load(String);
    
    HttpUrl get();
    void set(HttpUrl);

    String toString();

private:
    HttpUrl mUrl;
};

}
#endif
