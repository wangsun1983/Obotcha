#ifndef __OBOTCHA_HTTP_HEADER_CONTENT_PARSER_HPP__
#define __OBOTCHA_HTTP_HEADER_CONTENT_PARSER_HPP__

#include <functional>

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

using _ParseResult = std::function<void(String,String)>;

DECLARE_CLASS(HttpHeaderContentParser) {

  public:
    _HttpHeaderContentParser() = default;
    static int skipUntil(String input, int pos, String characters);
    static int skipWhitespace(String input, int pos);
    static int parseSeconds(String value, int defaultValue);
    static int load(String content,const _ParseResult &);
    static int load(String content,String skipdirective,String skieparam,const _ParseResult &);
};

} // namespace obotcha
#endif
