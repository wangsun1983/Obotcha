#ifndef __OBOTCHA_HTTP_HEADER_LOCATION_HPP__
#define __OBOTCHA_HTTP_HEADER_LOCATION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderLocation) {

public:
    _HttpHeaderLocation();
    _HttpHeaderLocation(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String location;
};

}
#endif
