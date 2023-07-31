#ifndef __OBOTCHA_HTTP_HEADER_RETRY_AFTER_HPP__
#define __OBOTCHA_HTTP_HEADER_RETRY_AFTER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderRetryAfter) {

public:
    _HttpHeaderRetryAfter() = default;
    explicit _HttpHeaderRetryAfter(String);

    void load(String);
    HttpDate getDate() const;
    int getDelayInterval() const;

    void setDate(HttpDate);
    void setDelayInterval(int);

    String toString();

private:
    HttpDate date = nullptr;
    int delay = -1;
};

}
#endif
