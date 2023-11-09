#ifndef __OBOTCHA_HTTP_V2_FRAME_TRANSMITTER_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_TRANSMITTER_HPP__

#include "Object.hpp"
#include "Thread.hpp"
#include "Mutex.hpp"
#include "FileInputStream.hpp"
#include "LinkedList.hpp"
#include "Http2LocalFlowController.hpp"
#include "List.hpp"
#include "Condition.hpp"
#include "BlockingQueue.hpp"
#include "Http2FrameByteArray.hpp"
#include "Http2SettingFrame.hpp"

namespace obotcha {

class _Http2Stream;

DECLARE_CLASS(FrameTransmitterBase) {
public:
    sp<_Http2Stream> stream;
    int index;
};

DECLARE_CLASS(FrameTransmitterSetting) IMPLEMENTS(FrameTransmitterBase){
public:    
    _FrameTransmitterSetting(sp<_Http2Stream>,Http2SettingFrame);
    Http2SettingFrame frame;
};

DECLARE_CLASS(FrameTransmitterHeader) IMPLEMENTS(FrameTransmitterBase){
public:    
    _FrameTransmitterHeader(sp<_Http2Stream>,Http2FrameByteArray,int index  = 0);
    Http2FrameByteArray data;
};


DECLARE_CLASS(FrameTransmitterContent) IMPLEMENTS(FrameTransmitterBase){
public:    
    _FrameTransmitterContent(sp<_Http2Stream>,ByteArray,int index  = 0);
    ByteArray data;
};

DECLARE_CLASS(FrameTransmitterFile) IMPLEMENTS(FrameTransmitterBase){
public:
    _FrameTransmitterFile(sp<_Http2Stream>,FileInputStream);
    FileInputStream mFileInputStream;
    ~_FrameTransmitterFile();
};

DECLARE_CLASS(Http2FrameTransmitter) IMPLEMENTS(Thread) {
public:
    _Http2FrameTransmitter(Http2LocalFlowController c);
    void run();
    void onWindowUpdate(int streamid,uint32_t size);
    void submitFile(sp<_Http2Stream>,FileInputStream);
    void submitContent(sp<_Http2Stream>,ByteArray);
    void submitHeader(sp<_Http2Stream>,Http2FrameByteArray);
    void submitSetting(sp<_Http2Stream>,Http2SettingFrame);
    void destroy();
    int getDefaultSendSize();

public:
    static uint32_t kDefaultSendSize;
    int send(FrameTransmitterContent content);
    int send(FrameTransmitterFile content);
    int send(FrameTransmitterHeader content);
    int send(FrameTransmitterSetting content);

    uint32_t mSendSize;
    Mutex mWaitMapMutex;
    List<LinkedList<FrameTransmitterBase>> mWaitDispatchDatas;
    List<LinkedList<FrameTransmitterBase>> mWaitDispatchHeaders;

    Http2LocalFlowController mFlowController;
    Condition mWaitCond;
    bool isRunning = true;

    BlockingQueue<Integer> mWindowUpdateStreams;
};

}
#endif
