#ifndef __OBOTCHA_HTTP_HEADER_CONTENT_PARSER_HPP__
#define __OBOTCHA_HTTP_HEADER_CONTENT_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpHeaderContentParser) {

public:
    _HttpHeaderContentParser();
    static int skipUntil(String input, int pos, String characters);
    static int skipWhitespace(String input, int pos);
    static int parseSeconds(String value, int defaultValue);
};

}
#endif
