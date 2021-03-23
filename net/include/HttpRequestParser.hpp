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
#include "HttpHeaderParser.hpp"

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

    enum HttpSubStatus {
        None = 0,
        HeadKeyValueParse,
    };
    
    int mStatus;

    int mSubStatus;

    ByteRingArray mBuff;

    ByteRingArrayReader mReader;

    Enviroment mEnv;

    int mBodyStartCount;

    String mHeaderName;
    
    String mHeaderValue;

    HttpPacket mHttpPacket;

    HttpMultiPartParser mMultiPartParser;

    HttpHeaderParser mHttpHeaderParser;
    
    HttpChunkParser mChunkParser;
};

}

#endif
