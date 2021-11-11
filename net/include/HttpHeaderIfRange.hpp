#ifndef __OBOTCHA_HTTP_IF_RANGE_HPP__
#define __OBOTCHA_HTTP_IF_RANGE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderIfRange) {

public:
    _HttpHeaderIfRange();
    _HttpHeaderIfRange(String);

    void import(String);

    HttpDate getDate();
    String getTag();

    void set(HttpDate);
    void set(String);

    String toString();

private:
    HttpDate date;
    String tag;
};

}
#endif
