#ifndef __OBOTCHA_HTTP__RESPONSE_PARSER_HPP__
#define __OBOTCHA_HTTP__RESPONSE_PARSER_HPP__

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
#include "HttpResponse.hpp"
#include "HttpPacket.hpp"
#include "HttpHeaderParser.hpp"
#include "HttpChunkParser.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpResponseParser) {

public:
    _HttpResponseParser();

    void pushHttpData(ByteArray);

    ArrayList<HttpPacket> doParse();

    int getStatus();

    HttpPacket parseEntireResponse(String response);

private:
    enum HttpParseStatus {
        Idle = 0,
        Body,
    };
    
    int mStatus;

    ByteRingArray mBuff;

    ByteRingArrayReader mReader;

    HttpPacket mHttpPacket;

    HttpHeaderParser mHttpHeaderParser;
    HttpChunkParser mChunkParser;
    
};

}

#endif
