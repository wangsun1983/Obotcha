#ifndef __OBOTCHA_HTTP_HEADER_EXPIRES_HPP__
#define __OBOTCHA_HTTP_HEADER_EXPIRES_HPP__

#include "Object.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderExpires) {

public:
    _HttpHeaderExpires();
    explicit _HttpHeaderExpires(String);

    void load(String);

    HttpDate get();
    void set(HttpDate);

    String toString();

private:
    HttpDate date;
};

}
#endif
