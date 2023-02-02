#include "Http2StreamSender.hpp"
#include "Http2Frame.hpp"
#include "Http2PriorityByteArray.hpp"

namespace obotcha {

_Http2StreamSender::_Http2StreamSender(OutputStream out) {
    this->out = out;
    list = createList<ConcurrentQueue<ByteArray>>(st(Http2Frame)::MaxWeight);
    for(int i = 0;i<st(Http2Frame)::MaxWeight;i++) {
        list[i] = createConcurrentQueue<ByteArray>();
    }

    mMutex = createMutex();
    mCondition = createCondition();
    isRunning = true;
}

void _Http2StreamSender::write(Http2PriorityByteArray b) {
    printf("http2streamSender write \n");
    int priority = b->getPriorityWeight();
    auto l = list[priority];
    l->putLast(b);

    AutoLock ll(mMutex);
    mCondition->notify();
}

void _Http2StreamSender::close() {
    printf("http2streamSender close \n");
    isRunning = false;
}

void _Http2StreamSender::run() {
    while(isRunning) {
        ConcurrentQueue<ByteArray> queue = nullptr;
        {
            AutoLock l(mMutex);
            for(int i = 0; i<st(Http2Frame)::MaxWeight;i++) {
                auto ll = list[i];
                if(ll->size() != 0) {
                    queue = ll;
                    break;
                }
            }

            if(queue == nullptr) {
                mCondition->wait(mMutex);
                continue;
            }
        }

        while(queue->size() != 0) {
            printf("http2streamSender write size is %d\n",queue->size());
            auto d = queue->takeFirst();
            out->write(d);
        }
    }
}

}
