#ifndef __OBOTCHA_HTTP_V2_LOCAL_FLOW_CONTROLLER_HPP__
#define __OBOTCHA_HTTP_V2_LOCAL_FLOW_CONTROLLER_HPP__

#include "Object.hpp"
#include "OutputStream.hpp"
#include "HashMap.hpp"

namespace obotcha {

class _Http2FrameTransmitter;

DECLARE_CLASS(LocalWindowSizeRecord) {
public:
    _LocalWindowSizeRecord(uint32_t setting);
    uint32_t current;
    uint32_t settting;
};

DECLARE_CLASS(Http2LocalFlowController) {
public:
    _Http2LocalFlowController();
    void bindDispatcher(sp<_Http2FrameTransmitter> dispatcher);
    void monitor(int streamid);
    uint32_t computeSendSize(int streamid,uint32_t expectedSize);
    void unMonitor(int streamid);
    void updateWindowSize(int streamdId,uint32_t size);
    void destroy();

    void setDefaultWindowSize(uint32_t window);
    uint32_t getDefaultWindowSize();

private:
    uint32_t mConnectionCurrent = 0;
    uint32_t mConnectionSetting = 0;
    HashMap<int,LocalWindowSizeRecord> mStreamWindowSizeMap;
    sp<_Http2FrameTransmitter> mDispatcher;
};

}

#endif
