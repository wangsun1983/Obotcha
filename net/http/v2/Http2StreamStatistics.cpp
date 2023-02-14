#include "Http2StreamStatistics.hpp"

namespace obotcha {

_Http2StreamStatistics::_Http2StreamStatistics() {
    mMutex = createMutex();
    mRetainFrameSize = createHashMap<int,Uint32>();
}

void _Http2StreamStatistics::updateFrameSize(int streamId,uint32_t size) {
    AutoLock l(mMutex);
    auto value = mRetainFrameSize->get(streamId);
    if(value != nullptr) {
        auto v = value->toValue();
        if(v < size) {
            value->update(0);
        } else {
            value->update(v - size);
        }
    }
}

uint32_t _Http2StreamStatistics::getRetainFrameSize(int streamId) {
    AutoLock l(mMutex);
    auto value = mRetainFrameSize->get(streamId);
    return value == nullptr?0:value->toValue();
}

}
