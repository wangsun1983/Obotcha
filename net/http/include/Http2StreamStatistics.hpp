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
    void setMaxFrameSize(uint32_t);
    uint32_t getMaxFrameSize();

    void setMaxStreamCount(uint32_t);
    uint32_t getMaxStreamCount();

    void setWindowSize(uint32_t);
    uint32_t getWindowSize();

    _Http2StreamStatistics();

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
   Mutex mMutex;
   HashMap<int,Uint32> mRetainFrameSize;
   uint32_t mStreamCount;
   int mWindowSize;

   uint32_t mMaxFrameSize;
   uint32_t mMaxStreamCount;

};

}

#endif
