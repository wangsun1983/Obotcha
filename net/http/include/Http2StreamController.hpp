#ifndef __OBOTCHA_HTTP_V2_STREAM_CONTROLLER_HPP__
#define __OBOTCHA_HTTP_V2_STREAM_CONTROLLER_HPP__

#include "Object.hpp"
#include "HPackEncoder.hpp"
#include "HPackDecoder.hpp"
#include "Http2Stream.hpp"
#include "Http2SettingFrame.hpp"
#include "HashMap.hpp"
#include "HttpPacket.hpp"
#include "Http2FrameParser.hpp"
#include "Http2ShakeHandFrame.hpp"
#include "Mutex.hpp"
#include "OutputStream.hpp"
#include "Base64.hpp"
#include "Http2StreamStatistics.hpp"
#include "Http2RemoteFlowController.hpp"
#include "Http2LocalFlowController.hpp"
#include "Http2DataFrameDispatcher.hpp"

namespace obotcha {

DECLARE_CLASS(Http2StreamController) IMPLEMENTS(HttpPacketParser){
public:
    _Http2StreamController(OutputStream,Http2FrameOption option = nullptr);
    Http2Stream newStream();
    Http2Stream newStream(uint32_t);
    Http2Stream getStream(uint32_t);
    
    int pushData(ByteArray);
    ArrayList<HttpPacket> doParse();
    HttpPacket parseEntireRequest(ByteArray request);
    void reset();

    void postProcessing(ArrayList<HttpPacket> packets);
private:
    enum class Status {
        ShakeHand = 0,
        Preface,
        WaitFirstSetting,
        Comunicate
    };

    HPackEncoder encoder = createHPackEncoder();
    HPackDecoder decoder = createHPackDecoder();
    Mutex mMutex = createMutex();
    HashMap<Integer,Http2Stream> streams = createHashMap<Integer,Http2Stream>();

    //use to parse http2
    ByteRingArray mRingArray;
    Http2ShakeHandFrame shakeHandFrame;
    Http2FrameParser mFrameParser;
    ByteRingArrayReader mReader;
    int mIndex = 0;
    OutputStream out;
    Base64 mBase64 = createBase64();
    Http2StreamSender mSender;
    Status mStatus = Status::ShakeHand;
    ArrayList<Http2Frame> mFirstSettingCaches = createArrayList<Http2Frame>();
    Http2StreamStatistics mStatistics = createHttp2StreamStatistics();
    Http2RemoteFlowController mRemoteController;
    Http2LocalFlowController mLocalController;
    Http2DataFrameDispatcher mDataDispatcher;
};

}

#endif
