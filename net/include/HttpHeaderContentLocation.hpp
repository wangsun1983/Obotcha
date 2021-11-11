#ifndef __OBOTCHA_HTTP_CONTENT_LOCATION_HPP__
#define __OBOTCHA_HTTP_CONTENT_LOCATION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentLocation) {

public:
    _HttpHeaderContentLocation();
    _HttpHeaderContentLocation(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String location;
};

}
#endif
