#ifndef __OBOTCHA_HTTP_PACKET_PARSER_IMPL_HPP__
#define __OBOTCHA_HTTP_PACKET_PARSER_IMPL_HPP__

#include "Object.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpPacket.hpp"
#include "HttpMultiPartParser.hpp"
#include "HttpChunkParser.hpp"
#include "HttpHeaderParser.hpp"
#include "HttpPacketParser.hpp"
#include "HttpPriContentParser.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPacketParserImpl) IMPLEMENTS(HttpPacketParser) {

public:
    _HttpPacketParserImpl();

    explicit _HttpPacketParserImpl(ByteRingArray);

    int pushData(ByteArray);

    ArrayList<HttpPacket> doParse();

    void reset();

private:

    enum Status {
        Idle = 0,
        HeadStart,
        BodyStart,
    };

    void switchToIdle();
    bool isUpgradePacket();
    bool isConnectPacket();
    bool isClosePacket();
    bool isResponsePacket();

    ByteRingArray mBuff;
    ByteRingArrayReader mReader;

    int mStatus;

    HttpPacket mHttpPacket;

    HttpMultiPartParser mMultiPartParser;

    HttpHeaderParser mHttpHeaderParser;
    
    HttpChunkParser mChunkParser;

    HttpPriContentParser mPriContentParser;

    ByteArray mSavedContentBuff;

    //case CHUNKED_W_TRAILING_HEADERS
    //bool isChunkedWTrailingHeaders;
    
};

}

#endif
