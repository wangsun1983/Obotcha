#ifndef __OBOTCHA_HTTP_HEADER_ORIGIN_HPP__
#define __OBOTCHA_HTTP_HEADER_ORIGIN_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderOrigin) {

public:
    _HttpHeaderOrigin();
    _HttpHeaderOrigin(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String origin;
};

}
#endif
