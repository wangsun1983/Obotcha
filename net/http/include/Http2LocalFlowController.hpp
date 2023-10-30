#ifndef __OBOTCHA_HTTP_V2_LOCAL_FLOW_CONTROLLER_HPP__
#define __OBOTCHA_HTTP_V2_LOCAL_FLOW_CONTROLLER_HPP__

#include "Object.hpp"
#include "OutputStream.hpp"
#include "HashMap.hpp"

namespace obotcha {

class _Http2DataFrameDispatcher;

DECLARE_CLASS(LocalWindowSizeRecord) {
public:
    _LocalWindowSizeRecord(uint32_t setting);
    uint32_t current;
    uint32_t settting;
};

DECLARE_CLASS(Http2LocalFlowController) {
public:
    _Http2LocalFlowController();
    void bindDispatcher(sp<_Http2DataFrameDispatcher> dispatcher);
    void monitor(int streamid,uint32_t defaultWindowSize = 0);
    uint32_t computeSendSize(int streamid,uint32_t expectedSize);
    void unMonitor(int streamid);
    void updateWindowSize(int streamdId,uint32_t size);
    void destroy();
private:
    uint32_t mConnectionCurrent;
    uint32_t mConnectionSetting;
    HashMap<int,LocalWindowSizeRecord> mStreamWindowSizeMap;
    sp<_Http2DataFrameDispatcher> mDispatcher;
};

}

#endif
