#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_MAX_AGE_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_MAX_AGE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlMaxAge) {

public:
    _HttpHeaderAccessControlMaxAge();
    _HttpHeaderAccessControlMaxAge(String);

    void import(String);

    void set(int);

    int get();

    String toString();

private:
    int maxage;
};

}
#endif