#ifndef __OBOTCHA_HTTP_VERSION_PARSER_HPP__
#define __OBOTCHA_HTTP_VERSION_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpVersion.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpVersionParser) {

  public:
    static HttpVersion doParse(String);
};

} // namespace obotcha
#endif
