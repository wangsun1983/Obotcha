#ifndef __OBOTCHA_HTTP_HEADER_PRAGMA_HPP__
#define __OBOTCHA_HTTP_HEADER_PRAGMA_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderPragma) {

public:
    _HttpHeaderPragma();
    _HttpHeaderPragma(String);

    void import(String);

    String get();
    void set(String);

    String toString();

private:
    String pragma;
};

}
#endif
