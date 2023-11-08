#include "Http2LocalFlowController.hpp"
#include "Http2WindowUpdateFrame.hpp"
#include "Http2Stream.hpp"
#include "Http2SettingFrame.hpp"
#include "Inspect.hpp"
#include "Log.hpp"
#include "Http2FrameTransmitter.hpp"

namespace obotcha {

_LocalWindowSizeRecord::_LocalWindowSizeRecord(uint32_t record) {
    current = record;
    settting = record;
}

_Http2LocalFlowController::_Http2LocalFlowController() {
    mStreamWindowSizeMap = createHashMap<int,LocalWindowSizeRecord>();
}

void _Http2LocalFlowController::bindDispatcher(sp<_Http2FrameTransmitter> dispatcher) {
    mDispatcher = dispatcher;
}

void _Http2LocalFlowController::monitor(int streamid) {
    mStreamWindowSizeMap->put(streamid,createLocalWindowSizeRecord(mConnectionSetting));
}

void _Http2LocalFlowController::updateWindowSize(int streamId,uint32_t size) {
    if(streamId == 0) {
        mConnectionCurrent += size;
        return;
    }
    
    auto windowSizeRecord = mStreamWindowSizeMap->get(streamId);
    if(windowSizeRecord == nullptr) {
        LOG(ERROR)<<"unknow stream window update";
        return;
    }
    windowSizeRecord->current += size;
    mDispatcher->onWindowUpdate(streamId,size);
}

uint32_t _Http2LocalFlowController::computeSendSize(int streamid,uint32_t size) {
    auto record = mStreamWindowSizeMap->get(streamid);
    Inspect(record->current == 0,0);

    if(size > record->current) {
        auto actualsize = record->current;
        record->current = 0;
        return actualsize;
    }
    record->current -= size;
    return size;
}

void _Http2LocalFlowController::unMonitor(int streamid) {
    mStreamWindowSizeMap->remove(streamid);
}

void _Http2LocalFlowController::destroy() {
    mDispatcher = nullptr;
}

void _Http2LocalFlowController::setDefaultWindowSize(uint32_t window) {
    mConnectionSetting = window;
    mConnectionCurrent = window;
}

uint32_t _Http2LocalFlowController::getDefaultWindowSize() {
    return mConnectionSetting;
}

}

