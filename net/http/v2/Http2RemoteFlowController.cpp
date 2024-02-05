#include "Http2RemoteFlowController.hpp"
#include "Http2WindowUpdateFrame.hpp"
#include "Http2Stream.hpp"
#include "Http2SettingFrame.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_RemoteWindowSizeRecord::_RemoteWindowSizeRecord(uint32_t record) {
    current = record;
    settting = record;
}

_Http2RemoteFlowController::_Http2RemoteFlowController(OutputStream output,Mutex mutex,HashMap<Integer,Http2Stream> streams) {
    mOutput = output;
    mStreamWindowSizeMap = createHashMap<int,RemoteWindowSizeRecord>();
    this->mMutex = mutex;
    this->streams = streams;
}

void _Http2RemoteFlowController::monitor(int streamid) {
    if(streamid != 0) {
        mStreamWindowSizeMap->put(streamid,createRemoteWindowSizeRecord(mConnectionSetting));
    }
}

void _Http2RemoteFlowController::onReceive(int streamid,uint32_t size) {
    //TODO?shall we controll all stream's flow by stream 0's window size
    auto record = mStreamWindowSizeMap->get(streamid);
    printf("_Http2RemoteFlowController streamid is %d,size is %d,record size is %d \n",streamid,size,record->current);
    if(record->current < size 
        || (record->current - size) < record->settting*3/4) {
        Http2WindowUpdateFrame windowUpdateFrame = createHttp2WindowUpdateFrame();
        windowUpdateFrame->setStreamId(streamid);
        windowUpdateFrame->setWindowSize(record->settting);
        printf("_Http2RemoteFlowController,set window size is %ld \n",record->settting);
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

void _Http2RemoteFlowController::forceFirstWindowUpdate() {
    AutoLock l(mMutex);
    if(streams == nullptr) {
        return;
    }

    ForEveryOne(pair,streams) {
        int streamid = pair->getKey()->toValue();
        auto record = mStreamWindowSizeMap->get(streamid);
        Http2WindowUpdateFrame windowUpdateFrame = createHttp2WindowUpdateFrame();
        windowUpdateFrame->setStreamId(streamid);
        windowUpdateFrame->setWindowSize(record->current);
        mOutput->write(windowUpdateFrame->toFrameData());
    }
    streams = nullptr;
}

void _Http2RemoteFlowController::unMonitor(int streamid) {
    mStreamWindowSizeMap->remove(streamid);
}

void _Http2RemoteFlowController::setDefaultWindowSize(uint32_t window) {
    mConnectionCurrent = window;
    mConnectionSetting = window;
    //update stream 0
    mStreamWindowSizeMap->put(0,createRemoteWindowSizeRecord(mConnectionSetting));
}

uint32_t _Http2RemoteFlowController::getDefaultWindowSize() {
    return mConnectionSetting;
}

}

