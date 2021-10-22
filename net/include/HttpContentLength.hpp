#ifndef __OBOTCHA_HTTP_CONTENT_LENGTH_HPP__
#define __OBOTCHA_HTTP_CONTENT_LENGTH_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpContentLength) {

public:
    _HttpContentLength();
    _HttpContentLength(String);
    _HttpContentLength(int);

    void import(String);

    int get();
    void set(int);

    String toString();

private:
    int length;
};

}
#endif
