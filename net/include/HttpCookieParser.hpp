#ifndef __OBOTCHA_HTTP_COOKIE_PARSER_HPP__
#define __OBOTCHA_HTTP_COOKIE_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpCookie.hpp"

namespace obotcha {

DECLARE_CLASS(HttpCookieParser) {

public:
    static ArrayList<HttpCookie> parse(String);
};

}
#endif
