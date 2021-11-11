#ifndef __OBOTCHA_HTTP_IF_UNMODIFIED_SINCE_HPP__
#define __OBOTCHA_HTTP_IF_UNMODIFIED_SINCE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderIfUnmodifiedSince) {

public:
    _HttpHeaderIfUnmodifiedSince();
    _HttpHeaderIfUnmodifiedSince(String);

    void import(String);

    HttpDate get();
    void set(HttpDate);

    String toString();

private:
    HttpDate date;
};

}
#endif
