#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_ORIGIN_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_ORIGIN_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlAllowOrigin) {

public:
    _HttpHeaderAccessControlAllowOrigin();
    _HttpHeaderAccessControlAllowOrigin(String);

    void import(String);

    void set(String);

    String get();

    String toString();

private:
    String origin;
};

}
#endif