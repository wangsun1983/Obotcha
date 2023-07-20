#ifndef __OBOTCHA_HTTP_HEADER_SEC_FETCH_MODE_HPP__
#define __OBOTCHA_HTTP_HEADER_SEC_FETCH_MODE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecFetchMode) {

public:
    _HttpHeaderSecFetchMode();
    explicit _HttpHeaderSecFetchMode(String);

    void load(String);

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
