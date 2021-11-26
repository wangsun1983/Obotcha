#ifndef __OBOTCHA_HTTP_PACKET_PARSER_IMPL_HPP__
#define __OBOTCHA_HTTP_PACKET_PARSER_IMPL_HPP__

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
#include "HttpMultiPartParser.hpp"
#include "HttpChunkParser.hpp"
#include "HttpHeaderParser.hpp"
#include "HttpPacketParser.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPacketParserImpl) IMPLEMENTS(HttpPacketParser) {

public:
    _HttpPacketParserImpl();

    _HttpPacketParserImpl(ByteRingArray);

    int pushHttpData(ByteArray);

    ArrayList<HttpPacket> doParse();

    int getStatus();

    HttpPacket parseEntireRequest(String request);

    void reset();

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

    ByteArray mSavedContentBuff;

    //case CHUNKED_W_TRAILING_HEADERS
    bool isChunkedWTrailingHeaders;
    
};

}

#endif
