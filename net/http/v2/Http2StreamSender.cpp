#include "Http2StreamSender.hpp"
#include "Http2Frame.hpp"
#include "Http2FrameByteArray.hpp"
#include "Http2DataFrame.hpp"

namespace obotcha {

const int _Http2StreamSender::DefaultSendDataSize = 1024*32;

//--------Http2StreamControlRetainData--------
_Http2StreamControlRetainData::_Http2StreamControlRetainData(uint32_t index,Http2FrameByteArray data) {
    mIndex = index;
    mData = data;
}

//--------Http2StreamSender--------
_Http2StreamSender::_Http2StreamSender(OutputStream out,Http2StreamStatistics statistics) {
    this->out = out;
    this->mStatistics = statistics;    
    list = createList<ConcurrentQueue<Http2FrameByteArray>>(st(Http2Frame)::MaxWeight);
    for(int i = 0;i<st(Http2Frame)::MaxWeight;i++) {
        list[i] = createConcurrentQueue<Http2FrameByteArray>();
    }

    mMutex = createMutex();
    mCondition = createCondition();
    isRunning = true;
}

void _Http2StreamSender::write(Http2Frame frame) {
    //Http2FrameByteArray b = frame->toFrameData();
    auto l = list[frame->getWeight()];
    l->putLast(frame->toFrameData());

    // printf("type is %d,windowsize is %d \n",frame->getType(),mStatistics->getWindowSize());
    // //we should check whether windows is full????
    // if(frame->getType() == st(Http2Frame)::TypeData 
    //     && mStatistics->getWindowSize() == 0) {
    //     return;
    // }

    AutoLock ll(mMutex);
    mCondition->notify();
}

void  _Http2StreamSender::onUpdateWindowSize() {
    printf("Http2StreamSender onUpdate!!!! \n");
    AutoLock ll(mMutex);
    mCondition->notify();
}

void _Http2StreamSender::close() {
    isRunning = false;
}

void _Http2StreamSender::run() {
    while(isRunning) {
        ConcurrentQueue<Http2FrameByteArray> queue = nullptr;
        printf("_Http2StreamSender run trace0 \n");
        {
            AutoLock l(mMutex);
            bool isFound = false;
            for(int i = 0; i<st(Http2Frame)::MaxWeight;i++) {
                auto ll = list[i];
                if(ll->size() != 0) {
                    queue = ll;
                    isFound = true;
                    break;
                }
            }
            
            if(!isFound) {
                mCondition->wait(mMutex);
                continue;
            }
        }

        printf("_Http2StreamSender run trace1 \n");
        while(queue->size() != 0) {
            printf("_Http2StreamSender run trace2 \n");
            Http2FrameByteArray data = queue->takeFirst();
            out->write(data);
        }
    }
}

int _Http2StreamSender::send(Http2FrameByteArray data) {
    if(data->getType() == st(Http2Frame)::TypeData) {
        int windowSize = mStatistics->getWindowSize();
        int length = std::min(data->size(),DefaultSendDataSize);
        //recompose frame.
        if(length == data->size()) {
            //this is the last data
            Http2DataFrame frame = createHttp2DataFrame();
            frame->setData(data);
            frame->setEndStream(true);
            mStatistics->decWindowSize(out->write(frame->toFrameData()));
            return 0;
        } else {
            Http2DataFrame frame = createHttp2DataFrame();
            frame->setData(createByteArray(data->toValue(),length));
            frame->setEndStream(false);
            mStatistics->decWindowSize(out->write(frame->toFrameData()));
            return length;
        }
    }

    out->write(data);
    return 0;
}

}
