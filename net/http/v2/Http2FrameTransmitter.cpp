#include "Http2FrameTransmitter.hpp"
#include "Http2DataFrame.hpp"
#include "ForEveryOne.hpp"
#include "OStdInstanceOf.hpp"
#include "Http2Stream.hpp"
#include "Http2ContinuationFrame.hpp"

namespace obotcha {

_FrameTransmitterSetting::_FrameTransmitterSetting(sp<_Http2Stream> s ,Http2SettingFrame f) {
    stream = s;
    frame = f;
}

_FrameTransmitterHeader::_FrameTransmitterHeader(sp<_Http2Stream> s,Http2FrameByteArray d,int index) {
    data = d;
    this->index = index;
    stream = s;
}

_FrameTransmitterContent::_FrameTransmitterContent(Http2Stream s,ByteArray d,int index) {
    data = d;
    this->index = index;
    stream = s;
}

_FrameTransmitterFile::_FrameTransmitterFile(Http2Stream s,FileInputStream f) {
    mFileInputStream = f;
    mFileInputStream->open();
    stream = s;
}

_FrameTransmitterFile::~_FrameTransmitterFile() {
    mFileInputStream->close();
}

uint32_t _Http2FrameTransmitter::kDefaultSendSize = 16*1024;

_Http2FrameTransmitter::_Http2FrameTransmitter(Http2LocalFlowController c):mFlowController(c) {
    mWaitMapMutex = createMutex();
    mWaitCond = createCondition();
    mSendSize = kDefaultSendSize;
    mWaitDispatchDatas = createList<LinkedList<FrameTransmitterBase>>(1024);//TODO
    mWaitDispatchHeaders = createList<LinkedList<FrameTransmitterBase>>(1024);//TODO

    mWindowUpdateStreams = createBlockingQueue<Integer>();
}

void _Http2FrameTransmitter::onWindowUpdate(int streamid,uint32_t size) {
    mWindowUpdateStreams->putLast(createInteger(streamid));
}

void _Http2FrameTransmitter::run() {
    while(isRunning) {
        auto streamId = mWindowUpdateStreams->takeFirst();
        if(streamId == nullptr) {
            return;
        }

        {
            AutoLock l(mWaitMapMutex);
            auto list = mWaitDispatchDatas[streamId->toValue()];
            while(1) {
                auto item = list->peekFirst();
                if(item == nullptr) {
                    break;
                }

                if(IsInstance(FrameTransmitterContent,item)) {
                    auto dataContent = Cast<FrameTransmitterContent>(item);
                    if(send(dataContent) == 0) {
                        list->takeFirst();
                    } else {
                        break;
                    }
                } else if(IsInstance(FrameTransmitterFile,item)) {
                    auto dataFile = Cast<FrameTransmitterFile>(item);
                    if(send(dataFile) == 0) {
                        list->takeFirst();
                    } else {
                        break;
                    }
                } else if(IsInstance(FrameTransmitterHeader,item)) {
                    auto headContent = Cast<FrameTransmitterHeader>(item);
                    if(send(headContent) == 0) {
                        list->takeFirst();
                    } else {
                        break;
                    }
                } else if(IsInstance(FrameTransmitterSetting,item)) {
                    printf("Transmitter send setting frame \n");
                    auto settingContent = Cast<FrameTransmitterSetting>(item);
                    if(send(settingContent) == 0) {
                        list->takeFirst();
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

void _Http2FrameTransmitter::submitFile(Http2Stream stream,FileInputStream input) {
    AutoLock l(mWaitMapMutex);
    auto list = mWaitDispatchDatas[stream->getStreamId()];
    if(list == nullptr) {
        list = createLinkedList<FrameTransmitterBase>();
        mWaitDispatchDatas[stream->getStreamId()] = list;
    }
    printf("ansmitter::submitFile,trace1 stream id is %d \n",stream->getStreamId());
    auto item = createFrameTransmitterFile(stream,input);
    if(list->size() != 0) {
        printf("ansmitter::submitFile,trace2 stream id is %d \n",stream->getStreamId());
        list->putLast(item);
    } else {
        if(send(item) != 0) {
            printf("ansmitter::submitFile,trace3 stream id is %d \n",stream->getStreamId());
            list->putLast(item);
        }
    }
}

void _Http2FrameTransmitter::submitSetting(sp<_Http2Stream> stream,Http2SettingFrame frame) {
    AutoLock l(mWaitMapMutex);
    printf("ansmitter::submitSetting,trace1 stream id is %d \n",stream->getStreamId());
    auto list = mWaitDispatchDatas[stream->getStreamId()];
    if(list == nullptr) {
        list = createLinkedList<FrameTransmitterBase>();
        mWaitDispatchDatas[stream->getStreamId()] = list;
    }

    auto item = createFrameTransmitterSetting(stream,frame);
    if(list->size() != 0) {
        printf("ansmitter::submitSetting,trace2 stream id is %d \n",stream->getStreamId());
        list->putLast(item);
        mWindowUpdateStreams->putLast(createInteger(stream->getStreamId()));
    } else {
        printf("ansmitter::submitSetting,trace3 stream id is %d \n",stream->getStreamId());
        if(send(item) != 0) {
            printf("ansmitter::submitSetting,trace4 stream id is %d \n",stream->getStreamId());
            list->putLast(item);
            mWindowUpdateStreams->putLast(createInteger(stream->getStreamId()));
        }
    }
}

void _Http2FrameTransmitter::submitContent(Http2Stream stream,ByteArray data) {
    AutoLock l(mWaitMapMutex);
    int streamId = stream->getStreamId();
    auto list = mWaitDispatchDatas[stream->getStreamId()];
    if(list == nullptr) {
        list = createLinkedList<FrameTransmitterBase>();
        mWaitDispatchDatas[stream->getStreamId()] = list;
    }
    printf("ansmitter::submitContent,trace1 stream id is %d \n",stream->getStreamId());
    auto item = createFrameTransmitterContent(stream,data);
    if(list->size() != 0) {
        printf("ansmitter::submitContent,trace2 stream id is %d \n",stream->getStreamId());
        list->putLast(item);
    } else {
        if(send(item) != 0) {
            printf("ansmitter::submitContent,trace3 stream id is %d \n",stream->getStreamId());
            list->putLast(item);
        }
    }
}

void _Http2FrameTransmitter::submitHeader(sp<_Http2Stream> stream,Http2FrameByteArray data) {
    AutoLock l(mWaitMapMutex);
    printf("ansmitter::submitHeader,trace1 stream id is %d \n",stream->getStreamId());
    int streamId = stream->getStreamId();
    auto list = mWaitDispatchDatas[stream->getStreamId()];
    if(list == nullptr) {
        list = createLinkedList<FrameTransmitterBase>();
        mWaitDispatchDatas[stream->getStreamId()] = list;
    }

    if(list->size() != 0) {
        printf("ansmitter::submitHeader,trace2 stream id is %d \n",stream->getStreamId());
        list->putLast(createFrameTransmitterHeader(stream,data));
    } else {
        auto content = createFrameTransmitterHeader(stream,data);
        if(send(content) != 0) {
            printf("ansmitter::submitHeader,trace3 stream id is %d \n",stream->getStreamId());
            list->putLast(content);
        }
    }
}

int _Http2FrameTransmitter::send(FrameTransmitterFile content) {
    while(1) {
        ByteArray data = content->mFileInputStream->readAll();
        if(data == nullptr || data->size() == 0) {
            return 0;
        }

        auto sendData = createFrameTransmitterContent(content->stream,data);
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

int _Http2FrameTransmitter::send(FrameTransmitterHeader content) {
    while(1) {
        uint32_t expectSendSize = content->data->size() - content->index;
        if(expectSendSize > mSendSize) {
            expectSendSize = mSendSize;
        }
        auto actualSize = mFlowController->computeSendSize(content->stream->getStreamId(),mSendSize);
        if(actualSize == 0) {
            return -1;
        }

        if(expectSendSize < actualSize) {
            actualSize = expectSendSize;
        }

        Http2FrameByteArray data = createHttp2FrameByteArray(content->data,content->index,actualSize);
        //TODO
        //https://snyk.io/advisor/python/hyperframe/functions/hyperframe.frame.ContinuationFrame
        //# Check if we're in the middle of a headers block. If we are, this
        //# frame *must* be a CONTINUATION frame with the same stream ID as the
        //# leading HEADERS or PUSH_PROMISE frame. Anything else is a
        //# ProtocolError. If the frame *is* valid, append it to the header
        //# buffer.
        if(content->index == 0) {
            ByteArray newLengtData = createByteArray(4);
            ByteArrayWriter wr = createByteArrayWriter(newLengtData,st(IO)::Endianness::Big);
            /*remove the following size:
            +-----------------------------------------------+
            |                Length (24)                    |
            +---------------+---------------+---------------+
            |    0x1 (8)    | 00?0 ??0? (8) |
            +-+-------------+---------------+-------------------------------+
            |R|                Stream Identifier (31)                       |
            +-----------------------------------------------+
            */
            printf("first head frame data size is %ld \n",data->size());
            wr->write<int>(data->size() - 9);
            data[0] = newLengtData[1];
            data[1] = newLengtData[2];
            data[2] = newLengtData[3];
                        
            content->stream->directWriteData(data);
            content->index += actualSize;
            if(content->index == content->data->size()) {
                break;
            }
        } else {
            printf("Http2FrameTransmitter send trace2!!!!index is %ld,actualiSize is %ld \n",
                    content->index,actualSize);
            Http2ContinuationFrame continueFrame = createHttp2ContinuationFrame();
            continueFrame->setStreamId(content->stream->getStreamId());
            content->index += actualSize;
            bool isLastFrame = false;
            if(content->index == content->data->size()) {
                continueFrame->setEndHeaders(true);
                isLastFrame = true;
            }
            continueFrame->setHeadBlockFragment(data);
            auto d = continueFrame->toFrameData();
            printf("transmitter toFrameData,[0] is %x,[1] is %x,[2] is %x,[3] is %x,[4] is %x,[5] is %x,[6] is %x,[7] is %x  \n",
                        d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
            content->stream->getStreamState()->onSend(continueFrame);
            if(isLastFrame) {
                break;
            }
        }
    }

    return 0;
}

int _Http2FrameTransmitter::send(FrameTransmitterSetting content) {
    return content->stream->getStreamState()->onSend(content->frame);
}

int _Http2FrameTransmitter::send(FrameTransmitterContent content) {
    while(1) {
        uint32_t expectSendSize = content->data->size() - content->index;
        if(expectSendSize > mSendSize) {
            expectSendSize = mSendSize;
        }
        auto actualSize = mFlowController->computeSendSize(content->stream->getStreamId(),mSendSize);
        if(actualSize == 0) {
            return -1;
        }

        if(expectSendSize < actualSize) {
            actualSize = expectSendSize;
        }

        ByteArray data = createByteArray(content->data->toValue() + content->index,actualSize);
        printf("send data frame trace1,stream id is %d \n",content->stream->getStreamId());
        Http2DataFrame frame = createHttp2DataFrame();
        frame->setStreamId(content->stream->getStreamId());
        frame->setData(data);
        bool isLastFrame = false;
        if(content->index + actualSize == content->data->size()) {
            isLastFrame = true;
        }

        if(isLastFrame) {
            printf("send data frame trace2 \n");
            frame->setEndStream(true);
        }

        printf("send data frame trace4 \n");
        content->stream->getStreamState()->onSend(frame);
        if(!isLastFrame) {
            content->index += actualSize;
            printf("send trace4 \n");
            continue;
        }
        printf("send trace5 \n");
        break;
    }

    return 0;
}

void _Http2FrameTransmitter::destroy() {
    if(mFlowController != nullptr) {
        mFlowController->destroy();
        mFlowController = nullptr;
    }
    isRunning = false;
    mWindowUpdateStreams->destroy();

    {
        AutoLock l(mWaitMapMutex);
        if(mWaitDispatchDatas != nullptr) {
            ForEveryOne(list,mWaitDispatchDatas) {
                if(list != nullptr) {
                    list->clear();
                }
            }
            mWaitDispatchDatas = nullptr;
        }
    }
    join();
}

int _Http2FrameTransmitter::getDefaultSendSize() {
    return mSendSize;
}

}