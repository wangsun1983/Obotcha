#ifndef __OBOTCHA_HTTP_HEADER_LAST_MODIFIED_HPP__
#define __OBOTCHA_HTTP_HEADER_LAST_MODIFIED_HPP__

#include "Object.hpp"
#include "HttpDate.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderLastModified) {

public:
    _HttpHeaderLastModified();
    _HttpHeaderLastModified(String);

    void import(String);

    HttpDate get();
    void set(HttpDate);

    String toString();

private:
    HttpDate date;
};

}
#endif
