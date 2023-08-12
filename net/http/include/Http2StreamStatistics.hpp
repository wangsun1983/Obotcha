#ifndef __OBOTCHA_HTTP_STREAM_STATICS_HPP__
#define __OBOTCHA_HTTP_STREAM_STATICS_HPP__

#include "Object.hpp"
#include "Http2SettingFrame.hpp"
#include "Http2WindowUpdateFrame.hpp"
#include "Mutex.hpp"
#include "ConcurrentHashMap.hpp"

namespace obotcha {

//ThreadLocal
DECLARE_CLASS(Http2StreamStatistics) {

public:
    _Http2StreamStatistics() = default;

    void setMaxFrameSize(uint32_t);
    uint32_t getMaxFrameSize() const;

    void setMaxStreamCount(uint32_t);
    uint32_t getMaxStreamCount() const;

    void setWindowSize(uint32_t);
    uint32_t getWindowSize();

    //MaxFrameSize
    int updateFrameSize(int streamId,uint32_t size);
    uint32_t getRetainFrameSize(int streamid);

    //MaxStreamNums
    int decStreamCount();
    int incStreamCount();
    uint32_t getStreamCount();

    //windowSize
    int decWindowSize(uint32_t);
    int incWindowSize(uint32_t);
    
    void removeStream(uint32_t streamid);
    
private:
   Mutex mMutex = createMutex();
   HashMap<int,Uint32> mRetainFrameSize = createHashMap<int,Uint32>();
   uint32_t mStreamCount = 0;
   int mWindowSize = st(Http2FrameOption)::DefaultInitialWindowSize;

   uint32_t mMaxFrameSize = st(Http2FrameOption)::DefaultMaxFrameSize;
   uint32_t mMaxStreamCount = st(Http2FrameOption)::DefaultMaxConcurrentStreams;;

};

}

#endif
