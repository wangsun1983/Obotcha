#ifndef __HTTP_PARSER_HPP__
#define __HTTP_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpRequest.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpParser) {

public:
    _HttpParser();
    
    HttpRequest parseRequest(String);
   
private:
    HttpRequest mRequest;
    http_parser mParser;

    String mHeaderName;
    String mHeaderValue;

    static int on_message_begin(http_parser *);
    static int on_url(http_parser*, const char *at, size_t length);
    static int on_header_field(http_parser*, const char *at, size_t length);
    static int on_header_value(http_parser*, const char *at, size_t length);
    static int on_headers_complete(http_parser*, const char *at, size_t length);
    static int on_body(http_parser*, const char *at, size_t length);
    static int on_message_complete(http_parser *);
    static int on_reason(http_parser*, const char *at, size_t length);
    static int on_chunk_header(http_parser*);
    static int on_chunk_complete(http_parser*);
    static http_parser_settings settings;
};

}
#endif
