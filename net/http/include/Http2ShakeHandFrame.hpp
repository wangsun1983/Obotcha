#ifndef __OBOTCHA_HTTP_V2_SHAKE_HAND_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_SHAKE_HAND_FRAME_HPP__

#include "Object.hpp"
#include "ByteRingArray.hpp"
#include "ArrayList.hpp"
#include "HttpPacketParserImpl.hpp"

namespace obotcha {

DECLARE_CLASS(Http2ShakeHandFrame) {
public:
    explicit _Http2ShakeHandFrame(ByteRingArray);
    _Http2ShakeHandFrame() = default;

    ArrayList<HttpPacket> doParser();
    HttpPacket toShakeHandPacket(st(Net)::Protocol);
    ByteArray toPriString();
    
    static const String PreFace; 
private:
    HttpPacketParserImpl v1Parser; 
};

}

#endif
