#ifndef __OBOTCHA_HTTP_COOKIE_PARSER_HPP__
#define __OBOTCHA_HTTP_COOKIE_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpCookieParser) {

public:
    static HttpCookie parseCookie(String);
};

}
#endif
