#ifndef __OBOTCHA_HTTP_CONTENT_LOCATION_HPP__
#define __OBOTCHA_HTTP_CONTENT_LOCATION_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentLocation) {

public:
    _HttpHeaderContentLocation();
    explicit _HttpHeaderContentLocation(String);

    void load(String);
    String get();
    void set(String);
    String toString();

private:
    String location;
};
}
#endif
