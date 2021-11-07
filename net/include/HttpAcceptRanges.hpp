#ifndef __OBOTCHA_HTTP_ACCEPT_RANGES_HPP__
#define __OBOTCHA_HTTP_ACCEPT_RANGES_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAcceptRanges) {

public:
    _HttpAcceptRanges();
    _HttpAcceptRanges(String);

    void import(String);

    void set(String);
    String get();

    String toString();

private:
    String range;
};

}
#endif
