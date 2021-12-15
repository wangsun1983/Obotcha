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

namespace obotcha {

DECLARE_CLASS(Http2StreamController) IMPLEMENTS(HttpPacketParser){
public:
    _Http2StreamController();
    Http2Stream newStream();
    
    int pushHttpData(ByteArray);
    ArrayList<HttpPacket> doParse();
    HttpPacket parseEntireRequest(ByteArray request);
    void reset();

private:
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

};

}

#endif
