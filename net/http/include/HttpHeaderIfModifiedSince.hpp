#ifndef __OBOTCHA_HTTP_IF_MODIFIED_SINCE_HPP__
#define __OBOTCHA_HTTP_IF_MODIFIED_SINCE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderIfModifiedSince) {

public:
    _HttpHeaderIfModifiedSince();
    _HttpHeaderIfModifiedSince(String);

    void import(String);

    HttpDate get();
    void set(HttpDate);

    String toString();

private:
    HttpDate date;
};

}
#endif