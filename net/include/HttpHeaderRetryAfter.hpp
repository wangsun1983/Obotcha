#ifndef __OBOTCHA_HTTP_HEADER_RETRY_AFTER_HPP__
#define __OBOTCHA_HTTP_HEADER_RETRY_AFTER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderRetryAfter) {

public:
    _HttpHeaderRetryAfter();
    _HttpHeaderRetryAfter(String);

    void import(String);
    HttpDate getDate();
    int getDelayInterval();

    void setDate(HttpDate);
    void setDelayInterval(int);

    String toString();

private:
    HttpDate date;
    int delay;
};

}
#endif
