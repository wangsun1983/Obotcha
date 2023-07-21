#ifndef __OBOTCHA_HTTP_HEADER_DATE_HPP__
#define __OBOTCHA_HTTP_HEADER_DATE_HPP__

#include "Object.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderDate) {

public:
    _HttpHeaderDate() = default;
    explicit _HttpHeaderDate(String);

    void load(String);

    HttpDate get();
    void set(HttpDate);

    String toString();

private:
    HttpDate date;
};

}
#endif
