#ifndef __OBOTCHA_HTTP_HEADER_SEC_FETCH_MODE_HPP__
#define __OBOTCHA_HTTP_HEADER_SEC_FETCH_MODE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecFetchMode) {

public:
    _HttpHeaderSecFetchMode();
    _HttpHeaderSecFetchMode(String);

    void import(String);

    void set(String);

    String get();

    String toString();

    const static String Cors;
    const static String Navigate;
    const static String NestedNavigate;
    const static String NoCors;
    const static String SameOrigin;
    const static String Websocket;

private:
    String value;
};

}
#endif
