#include "Http2RemoteFlowController.hpp"
#include "Http2WindowUpdateFrame.hpp"
#include "Http2Stream.hpp"
#include "Http2SettingFrame.hpp"

namespace obotcha {

_RemoteWindowSizeRecord::_RemoteWindowSizeRecord(uint32_t record) {
    current = record;
    settting = record;
}

_Http2RemoteFlowController::_Http2RemoteFlowController(uint32_t connectionWindowSize,OutputStream output) {
    mConnectionCurrent = connectionWindowSize;
    mConnectionSetting = connectionWindowSize;
    mOutput = output;
    mStreamWindowSizeMap = createHashMap<int,RemoteWindowSizeRecord>();
}

void _Http2RemoteFlowController::monitor(int streamid,uint32_t defaultWindowSiz) {
    mStreamWindowSizeMap->put(streamid,createRemoteWindowSizeRecord(defaultWindowSiz));
}

void _Http2RemoteFlowController::onReceive(int streamid,uint32_t size) {
    auto record = mStreamWindowSizeMap->get(streamid);

    if(record->current < size 
        || (record->current - size) < record->settting*3/4) {
        Http2WindowUpdateFrame windowUpdateFrame = createHttp2WindowUpdateFrame();
        windowUpdateFrame->setStreamId(streamid);
        windowUpdateFrame->setWindowSize(record->settting);
        mOutput->write(windowUpdateFrame->toFrameData());
        record->current = record->settting;
    } else {
        record->current -= size;
    }

    if(mConnectionCurrent < size ||
        mConnectionCurrent < mConnectionSetting*3/4) {
        Http2WindowUpdateFrame windowUpdateFrame = createHttp2WindowUpdateFrame();
        windowUpdateFrame->setStreamId(0);
        windowUpdateFrame->setWindowSize(record->settting);
        mOutput->write(windowUpdateFrame->toFrameData());
        mConnectionCurrent = mConnectionSetting;
    } else {
        mConnectionCurrent -= size;
    }
}

void _Http2RemoteFlowController::unMonitor(int streamid) {
    mStreamWindowSizeMap->remove(streamid);
}

}

