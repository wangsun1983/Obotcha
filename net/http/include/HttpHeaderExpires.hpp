#ifndef __OBOTCHA_HTTP_HEADER_EXPIRES_HPP__
#define __OBOTCHA_HTTP_HEADER_EXPIRES_HPP__

#include "Object.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderExpires) {

public:
    _HttpHeaderExpires();
    _HttpHeaderExpires(String);

    void import(String);

    HttpDate get();
    void set(HttpDate);

    String toString();

private:
    HttpDate date;
};

}
#endif