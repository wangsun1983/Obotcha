#ifndef __OBOTCHA_HTTP_METHOD_PARSER_HPP__
#define __OBOTCHA_HTTP_METHOD_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpMethodParser) {

public:
    static int doParse(String);
    static String doParse(int);

};

}
#endif
