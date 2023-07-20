#ifndef __OBOTCHA_HTTP_HEADER_LOCATION_HPP__
#define __OBOTCHA_HTTP_HEADER_LOCATION_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderLocation) {

public:
    _HttpHeaderLocation();
    explicit _HttpHeaderLocation(String);

    void load(String);

    String get();
    void set(String);

    String toString();

private:
    String location;
};

}
#endif
