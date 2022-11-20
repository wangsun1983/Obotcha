#ifndef __OBOTCHA_HTTP_V2_SHAKE_HAND_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_SHAKE_HAND_FRAME_HPP__

#include "Object.hpp"
#include "ByteRingArray.hpp"
#include "ArrayList.hpp"
#include "HttpPacketParserImpl.hpp"

namespace obotcha {

DECLARE_CLASS(Http2ShakeHandFrame) {
public:
    _Http2ShakeHandFrame(ByteRingArray);
    _Http2ShakeHandFrame();
    ArrayList<HttpPacket> doParser();

    HttpPacket toShakeHandPacket(int);
    ByteArray toPriString();
    
    static const String PreFace; 
private:
    HttpPacketParserImpl v1Parser; 
};

}

#endif
