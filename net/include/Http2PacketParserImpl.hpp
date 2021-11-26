#ifndef __OBOTCHA_HTTP_V2_PACKET_PARSER_IMPL_HPP__
#define __OBOTCHA_HTTP_V2_PACKET_PARSER_IMPL_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"
#include "HttpPacketParser.hpp"
#include "Http2ShakeHandFrameParser.hpp"

namespace obotcha {

DECLARE_CLASS(Http2PacketParserImpl) IMPLEMENTS(HttpPacketParser) {

public:
    _Http2PacketParserImpl();

    int pushHttpData(ByteArray);

    ArrayList<HttpPacket> doParse();

    int getStatus();

    HttpPacket parseEntireRequest(ByteArray request);

    void reset();

private:
    enum Status {
        ShakeHand = 0,
        Preface,
        Comunicated,
    };
    
    Http2ShakeHandFrameParser mShakeHandParser;

    int mStatus;

    ByteRingArray mRingArray;
};

}

#endif
