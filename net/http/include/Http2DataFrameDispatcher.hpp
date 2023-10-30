#ifndef __OBOTCHA_HTTP_V2_DATA_FRAME_DISPATCHER_HPP__
#define __OBOTCHA_HTTP_V2_DATA_FRAME_DISPATCHER_HPP__

#include "Object.hpp"
#include "Thread.hpp"
#include "Mutex.hpp"
#include "FileInputStream.hpp"
#include "LinkedList.hpp"
#include "Http2LocalFlowController.hpp"
#include "List.hpp"
#include "Condition.hpp"
#include "BlockingQueue.hpp"

namespace obotcha {

class _Http2Stream;

DECLARE_CLASS(DataFrameDispatchBase) {
public:
    sp<_Http2Stream> stream;
    int index;
};

DECLARE_CLASS(DataFrameDispatchContent) IMPLEMENTS(DataFrameDispatchBase){
public:    
    _DataFrameDispatchContent(sp<_Http2Stream>,ByteArray,int index  = 0);
    ByteArray data;
};

DECLARE_CLASS(DataFrameDispatchFile) IMPLEMENTS(DataFrameDispatchBase){
public:
    _DataFrameDispatchFile(sp<_Http2Stream>,FileInputStream);
    FileInputStream mFileInputStream;
    ~_DataFrameDispatchFile();
};

DECLARE_CLASS(Http2DataFrameDispatcher) IMPLEMENTS(Thread) {
public:
    _Http2DataFrameDispatcher(Http2LocalFlowController c);
    void run();
    void onWindowUpdate(int streamid,uint32_t size);
    void submitFile(sp<_Http2Stream>,FileInputStream);
    void submitContent(sp<_Http2Stream>,ByteArray);
    void destroy();

public:
    static uint32_t kDefaultSendSize;
    int send(DataFrameDispatchContent content);
    int send(DataFrameDispatchFile content);

    uint32_t mSendSize;
    Mutex mWaitMapMutex;
    List<LinkedList<DataFrameDispatchBase>> mWaitDispatchDatas;
    Http2LocalFlowController mFlowController;
    Condition mWaitCond;
    bool isRunning = true;

    BlockingQueue<Integer> mWindowUpdateStreams;
    
};

}
#endif
