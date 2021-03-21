#ifndef __OBOTCHA_HTTP_VERSION_PARSER_HPP__
#define __OBOTCHA_HTTP_VERSION_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpVersion.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpVersionParser) {

public:
    static HttpVersion doParse(String);
};

}
#endif
