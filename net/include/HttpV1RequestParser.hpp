#ifndef __OBOTCHA_HTTP_V1_REQUEST_PARSER_HPP__
#define __OBOTCHA_HTTP_V1_REQUEST_PARSER_HPP__

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
#include "HttpCookieParser.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpV1RequestParser) {

public:
    _HttpV1RequestParser();

    void pushHttpData(ByteArray);

    ArrayList<HttpPacket> doParse();

    int getStatus();

    HttpPacket parseEntireResponse(String response);

    HttpPacket parseEntireRequest(String request);

private:
    enum HttpV1ParseStatus {
        HttpV1ParseStatusIdle = 0,
        HttpClientParseStatusHeadStart,
        HttpClientParseStatusBodyStart
    };
    
    int mStatus;

    ByteRingArray mBuff;

    ByteRingArrayReader mReader;

    Enviroment mEnv;

    int mHeadEndCount;

    int mChunkEndCount;

    http_parser mParser;

    String mHeaderName;
    
    String mHeaderValue;

    HttpPacket mHttpPacket;

    HttpMultiPartParser mMultiPartParser;

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