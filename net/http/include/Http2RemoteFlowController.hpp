#ifndef __OBOTCHA_HTTP_V2_REMOTE_FLOW_CONTROLLER_HPP__
#define __OBOTCHA_HTTP_V2_REMOTE_FLOW_CONTROLLER_HPP__

#include "Object.hpp"
#include "OutputStream.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_CLASS(RemoteWindowSizeRecord) {
public:
    _RemoteWindowSizeRecord(uint32_t setting);
    uint32_t current;
    uint32_t settting;
};

DECLARE_CLASS(Http2RemoteFlowController) {
public:
    _Http2RemoteFlowController(OutputStream output);
    void monitor(int streamid);
    void onReceive(int streamid,uint32_t size);
    void unMonitor(int streamid);

    void setDefaultWindowSize(uint32_t window);
    uint32_t getDefaultWindowSize();

private:
    uint32_t mConnectionCurrent = 0;
    uint32_t mConnectionSetting = 0;
    HashMap<int,RemoteWindowSizeRecord> mStreamWindowSizeMap;
    OutputStream mOutput;
};

}

#endif
