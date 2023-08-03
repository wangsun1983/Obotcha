#ifndef __OBOTCHA_HTTP_V2_STREAM_SENDER_HPP__
#define __OBOTCHA_HTTP_V2_STREAM_SENDER_HPP__

#include "Object.hpp"
#include "Byte.hpp"
#include "ConcurrentQueue.hpp"
#include "ConcurrentHashMap.hpp"
#include "ByteArray.hpp"
#include "OutputStream.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "List.hpp"
#include "Http2FrameByteArray.hpp"
#include "Thread.hpp"
#include "Http2Frame.hpp"
#include "Http2StreamStatistics.hpp"

namespace obotcha {

DECLARE_CLASS(Http2StreamControlRetainData) {
public:
    _Http2StreamControlRetainData(uint32_t index,Http2FrameByteArray data);
    uint32_t mIndex;
    Http2FrameByteArray mData;
};

DECLARE_CLASS(Http2StreamSender) IMPLEMENTS(Thread){
public:
    _Http2StreamSender(OutputStream,Http2StreamStatistics);
    void write(Http2Frame);
    void close();

    void onUpdateWindowSize();

private:
    static const int DefaultSendDataSize;
    void run();

    int send(Http2FrameByteArray);

    Mutex mMutex;
    Condition mCondition;
    List<ConcurrentQueue<Http2FrameByteArray>> list;

    Http2StreamControlRetainData mReatinData;
    OutputStream out;
    bool isRunning; //TODO
    Http2StreamStatistics mStatistics;
};

}

#endif
