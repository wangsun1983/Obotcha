#ifndef __OBOTCHA_HTTP_V2_SHAKE_HAND_FRAME_PARSER_HPP__
#define __OBOTCHA_HTTP_V2_SHAKE_HAND_FRAME_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacketParserImpl.hpp"

namespace obotcha {

DECLARE_CLASS(Http2ShakeHandFrameParser) {
public:
    _Http2ShakeHandFrameParser(ByteRingArray);

    ArrayList<HttpPacket> doParser();

private:

    HttpPacketParserImpl v1Parser; 
};

}

#endif
