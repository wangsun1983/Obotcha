#ifndef __OBOTCHA_HTTP_HEADER_DNT_HPP__
#define __OBOTCHA_HTTP_HEADER_DNT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderDnt) {

public:
    _HttpHeaderDnt();
    _HttpHeaderDnt(String);

    void import(String);

    void set(int);

    int get();

    String toString();

private:
    int dnt;
};

}
#endif
