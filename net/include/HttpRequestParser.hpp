#ifndef __OBOTCHA_HTTP__REQUEST_PARSER_HPP__
#define __OBOTCHA_HTTP__REQUEST_PARSER_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"
#include "HttpUrl.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "Enviroment.hpp"
#include "HttpPacket.hpp"
#include "http_parser.h"
#include "HttpMultiPartParser.hpp"
#include "HttpChunkParser.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRequestParser) {

public:
    _HttpRequestParser();

    int pushHttpData(ByteArray);

    ArrayList<HttpPacket> doParse();

    int getStatus();

    HttpPacket parseEntireRequest(String request);

private:
    enum HttpParseStatus {
        Idle = 0,
        HeadStart,
        BodyStart
    };
    
    int mStatus;

    ByteRingArray mBuff;

    ByteRingArrayReader mReader;

    Enviroment mEnv;

    int mHeadEndCount;

    http_parser mParser;

    String mHeaderName;
    
    String mHeaderValue;

    HttpPacket mHttpPacket;

    HttpMultiPartParser mMultiPartParser;
    
    HttpChunkParser mChunkParser;

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
