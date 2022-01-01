#ifndef __OBOTCHA_HTTP_V2_STREAM_CONTROLLER_HPP__
#define __OBOTCHA_HTTP_V2_STREAM_CONTROLLER_HPP__

#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HPackEncoder.hpp"
#include "HPackDecoder.hpp"
#include "Http2Frame.hpp"
#include "Http2Stream.hpp"
#include "HashMap.hpp"
#include "HttpPacket.hpp"
#include "Http2FrameParser.hpp"
#include "Http2ShakeHandFrame.hpp"
#include "Mutex.hpp"
#include "Http2Packet.hpp"
#include "OutputStream.hpp"
#include "Base64.hpp"
#include "HttpPacketWriter.hpp"

namespace obotcha {

DECLARE_CLASS(Http2StreamController) IMPLEMENTS(HttpPacketParser){
public:
    _Http2StreamController(OutputStream);
    Http2Stream newStream();
    Http2Stream newStream(uint32_t);
    Http2Stream getStream(uint32_t);
    
    int pushHttpData(ByteArray);
    ArrayList<HttpPacket> doParse();
    HttpPacket parseEntireRequest(ByteArray request);
    void reset();

private:
    enum ControllerStatus {
        ShakeHand = 0,
        Preface,
        Comunicate
    };

    HPackEncoder encoder;
    HPackDecoder decoder;

    Mutex mMutex;
    HashMap<Integer,Http2Stream> streams;

    //use to parse http2
    ByteRingArray mRingArray;
    Http2ShakeHandFrame shakeHandFrame;
    Http2FrameParser mFrameParser;
    ByteRingArrayReader mReader;
    int mIndex;

    OutputStream out;

    Base64 mBase64;

    Http2StreamSender mSender;

};

}

#endif
