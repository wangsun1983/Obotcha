#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_RANGES_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_RANGES_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptRanges) {

public:
    _HttpHeaderAcceptRanges();
    _HttpHeaderAcceptRanges(String);

    void import(String);

    void set(String);
    String get();

    String toString();

private:
    String range;
};

}
#endif
