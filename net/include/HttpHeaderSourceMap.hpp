#ifndef __OBOTCHA_HTTP_HEADER_SOURCE_MAP_HPP__
#define __OBOTCHA_HTTP_HEADER_SOURCE_MAP_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSourceMap) {

public:
    _HttpHeaderSourceMap();
    _HttpHeaderSourceMap(String);

    void import(String);

    void set(String);

    String get();

    String toString();

private:
    String url;
};

}
#endif
