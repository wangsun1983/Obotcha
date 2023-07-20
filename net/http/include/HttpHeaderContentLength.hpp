#ifndef __OBOTCHA_HTTP_CONTENT_LENGTH_HPP__
#define __OBOTCHA_HTTP_CONTENT_LENGTH_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentLength) {

public:
    _HttpHeaderContentLength();
    explicit _HttpHeaderContentLength(String);
    explicit _HttpHeaderContentLength(int);

    void load(String);

    int get();
    void set(int);

    String toString();

private:
    int length;
};

}
#endif
