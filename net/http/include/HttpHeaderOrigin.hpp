#ifndef __OBOTCHA_HTTP_HEADER_ORIGIN_HPP__
#define __OBOTCHA_HTTP_HEADER_ORIGIN_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderOrigin) {

public:
    _HttpHeaderOrigin() = default;
    explicit _HttpHeaderOrigin(String);

    void load(String);
    
    HttpUrl get();
    void set(HttpUrl);

    String toString() override;

private:
    HttpUrl mUrl = createHttpUrl();
};

}
#endif
