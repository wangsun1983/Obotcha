#ifndef __OBOTCHA_HTTP_HEADER_SEC_FETCH_SITE_HPP__
#define __OBOTCHA_HTTP_HEADER_SEC_FETCH_SITE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecFetchSite) {

public:
    _HttpHeaderSecFetchSite();
    _HttpHeaderSecFetchSite(String);

    void import(String);

    void set(String);

    String get();

    String toString();

    const static String CrossSite;
    const static String SameOrigin;
    const static String SameSite;
    const static String None;

private:
    String value;
};

}
#endif
