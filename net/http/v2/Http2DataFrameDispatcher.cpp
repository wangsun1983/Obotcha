#include "Http2DataFrameDispatcher.hpp"
#include "Http2DataFrame.hpp"
#include "ForEveryOne.hpp"
#include "OStdInstanceOf.hpp"
#include "Http2Stream.hpp"

namespace obotcha {

_DataFrameDispatchContent::_DataFrameDispatchContent(Http2Stream s,ByteArray d,int index) {
    data = d;
    this->index = index;
    stream = s;
}

_DataFrameDispatchFile::_DataFrameDispatchFile(Http2Stream s,FileInputStream f) {
    mFileInputStream = f;
    mFileInputStream->open();
    stream = s;
}

_DataFrameDispatchFile::~_DataFrameDispatchFile() {
    mFileInputStream->close();
}

uint32_t _Http2DataFrameDispatcher::kDefaultSendSize = 64*1024;

_Http2DataFrameDispatcher::_Http2DataFrameDispatcher(Http2LocalFlowController c):mFlowController(c) {
    mWaitMapMutex = createMutex();
    mWaitCond = createCondition();
    mSendSize = kDefaultSendSize;
    mWaitDispatchDatas = createList<LinkedList<DataFrameDispatchBase>>(1024);//TODO
    mWindowUpdateStreams = createBlockingQueue<Integer>();
}

void _Http2DataFrameDispatcher::onWindowUpdate(int streamid,uint32_t size) {
    mWindowUpdateStreams->putLast(createInteger(streamid));
}

void _Http2DataFrameDispatcher::run() {
    while(isRunning) {
        auto streamId = mWindowUpdateStreams->takeFirst();
        {
            AutoLock l(mWaitMapMutex);
            auto list = mWaitDispatchDatas[streamId->toValue()];
            while(1) {
                auto item = list->peekFirst();
                if(item == nullptr) {
                    break;
                }

                if(IsInstance(DataFrameDispatchContent,item)) {
                    auto dataContent = Cast<DataFrameDispatchContent>(item);
                    if(send(dataContent) == 0) {
                        list->takeFirst();
                    } else {
                        break;
                    }
                } else if(IsInstance(DataFrameDispatchFile,item)) {
                    auto dataFile = Cast<DataFrameDispatchFile>(item);
                    if(send(dataFile) == 0) {
                        list->takeFirst();
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

void _Http2DataFrameDispatcher::submitFile(Http2Stream stream,FileInputStream input) {
    AutoLock l(mWaitMapMutex);
    auto list = mWaitDispatchDatas[stream->getStreamId()];
    if(list != nullptr || list->size() != 0) {
        list->putLast(DataFrameDispatchFile());
    } else {
        auto content = createDataFrameDispatchFile(stream,input);
        if(send(content) != 0) {
            list->putLast(content);
        }
    }
}

void _Http2DataFrameDispatcher::submitContent(Http2Stream stream,ByteArray data) {
    AutoLock l(mWaitMapMutex);
    int streamId = stream->getStreamId();
    auto list = mWaitDispatchDatas[stream->getStreamId()];
    if(list != nullptr || list->size() != 0) {
        list->putLast(createDataFrameDispatchContent(stream,data));
    } else {
        auto content = createDataFrameDispatchContent(stream,data);
        if(send(content) != 0) {
            list->putLast(content);
        }
    }
}

int _Http2DataFrameDispatcher::send(DataFrameDispatchFile content) {
    while(1) {
        ByteArray data = content->mFileInputStream->read(mSendSize);
        if(data == nullptr || data->size() == 0) {
            return 0;
        }

        auto sendData = createDataFrameDispatchContent(content->stream,data);
        if(send(sendData) == -1) {
            if(sendData->index == 0) {
                return -1;
            } else {
                //if we send patial data,seek again.
                content->mFileInputStream->seekTo(content->index + sendData->index);
                content->index += sendData->index;
            }
            return  -1;
        }
        content->index += mSendSize;
    }
}

int _Http2DataFrameDispatcher::send(DataFrameDispatchContent content) {
    while(1) {
        uint32_t expectSendSize = content->data->size() - content->index;
        if(expectSendSize > mSendSize) {
            expectSendSize = mSendSize;
        }

        auto actualSize = mFlowController->computeSendSize(content->stream->getStreamId(),mSendSize);
        if(actualSize == 0) {
            return -1;
        }

        ByteArray data = createByteArray(content->data->toValue() + content->index,actualSize);

        Http2DataFrame frame = createHttp2DataFrame();
        frame->setStreamId(content->stream->getStreamId());
        frame->setData(data);

        bool isLastFrame = false;
        if(content->index + actualSize == content->data->size() - 1) {
            isLastFrame = true;
        }

        if(isLastFrame) {
            frame->setEndStream(true);
        }

        content->stream->directWrite(frame);

        if(!isLastFrame) {
            content->index += actualSize;
            continue;
        }

        break;
    }

    return 0;
}

 void _Http2DataFrameDispatcher::destroy() {
    if(mFlowController != nullptr) {
        mFlowController->destroy();
        mFlowController = nullptr;
    }
 }

}
