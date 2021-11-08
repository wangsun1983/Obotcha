#ifndef __OBOTCHA_HTTP_HEADER_EXPIRES_HPP__
#define __OBOTCHA_HTTP_HEADER_EXPIRES_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpDate.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderDate) {

public:
    _HttpHeaderDate();
    _HttpHeaderDate(String);

    void import(String);

    HttpDate get();
    void set(HttpDate);

    String toString();

private:
    HttpDate date;
};

}
#endif
