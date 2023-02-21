#include "Http2StreamStatistics.hpp"
#include "Http2SettingFrame.hpp"

namespace obotcha {

_Http2StreamStatistics::_Http2StreamStatistics() {
    mMutex = createMutex();
    mRetainFrameSize = createHashMap<int,Uint32>();
    mMaxFrameSize = st(Http2FrameOption)::DefaultMaxFrameSize;
    mMaxStreamCount = st(Http2FrameOption)::DefaultMaxConcurrentStreams;
    mWindowSize = st(Http2FrameOption)::DefaultInitialWindowSize;
    mStreamCount = 0;
}

void _Http2StreamStatistics::setWindowSize(uint32_t size) {
    AutoLock l(mMutex);
    mWindowSize = size;
}

uint32_t _Http2StreamStatistics::getWindowSize() {
    AutoLock l(mMutex);
    return mWindowSize;
}

int _Http2StreamStatistics::decWindowSize(uint32_t size) {
    AutoLock l(mMutex);
    mWindowSize -= size;
    if(mWindowSize < 0) {
        mWindowSize = 0;
    }

    return mWindowSize;
}

int _Http2StreamStatistics::incWindowSize(uint32_t size) {
    AutoLock l(mMutex);
    mWindowSize += size;
    return mWindowSize;
}

int _Http2StreamStatistics::decStreamCount() {
    AutoLock l(mMutex);
    if(mStreamCount > 0) {
        mStreamCount--;
        return 0;
    }

    return -1;
}

int _Http2StreamStatistics::incStreamCount() {
    AutoLock l(mMutex);
    if(mStreamCount >= mMaxStreamCount) {
        return -1;
    }

    mStreamCount++;
    return 0;
}

uint32_t _Http2StreamStatistics::getStreamCount() {
    AutoLock l(mMutex);
    return mStreamCount;
}

int _Http2StreamStatistics::updateFrameSize(int streamId,uint32_t size) {
    AutoLock l(mMutex);
    auto value = mRetainFrameSize->get(streamId);
    printf("start updateFramesize trace1\n");
    if(value != nullptr) {
        printf("start updateFramesize trace2\n");
        auto v = value->toValue();
        printf("start updateFramesize trace2_1,v is %d\n",v);
        if(v < size) {
            value->update(0);
            return  -1;
        } else {
            value->update(v - size);
        }
    }
    printf("start updateFramesize trace3\n");

    return 0;
}

uint32_t _Http2StreamStatistics::getRetainFrameSize(int streamId) {
    AutoLock l(mMutex);
    auto value = mRetainFrameSize->get(streamId);
    return value == nullptr?0:value->toValue();
}

void _Http2StreamStatistics::setMaxFrameSize(uint32_t max) {
    mMaxFrameSize = max;
}

uint32_t _Http2StreamStatistics::getMaxFrameSize() {
    return mMaxFrameSize;
}

void _Http2StreamStatistics::setMaxStreamCount(uint32_t max) {
    mMaxStreamCount = max;
}

uint32_t _Http2StreamStatistics::getMaxStreamCount() {
    return mMaxStreamCount;
}

void _Http2StreamStatistics::removeStream(uint32_t streamId) {
    AutoLock l(mMutex);
    mRetainFrameSize->remove(streamId);
}



}
