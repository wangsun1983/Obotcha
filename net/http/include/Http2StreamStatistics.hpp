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
    _Http2StreamStatistics();
    void updateFrameSize(int streamId,uint32_t);
    uint32_t getRetainFrameSize(int streamid);

private:
   Mutex mMutex;
   HashMap<int,Uint32> mRetainFrameSize;

};

}

#endif
