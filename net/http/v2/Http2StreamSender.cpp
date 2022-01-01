#include "Http2StreamSender.hpp"
#include "Http2Frame.hpp"

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

void _Http2StreamSender::write(ByteArray b) {
    int priority = b->getPriorityWeight();
    auto l = list[priority];
    l->putLast(b);

    AutoLock ll(mMutex);
    mCondition->notify();
}

void _Http2StreamSender::close() {
    isRunning = false;
}

void _Http2StreamSender::run() {
    while(isRunning) {
        printf("Http2StreamSender run start \n");
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
            auto d = queue->takeFirst();
            printf("Http2StreamSender run write \n");
            out->write(d);
        }
    }
}

}
