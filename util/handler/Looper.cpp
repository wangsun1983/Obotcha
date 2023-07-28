#include "Looper.hpp"

namespace obotcha {

_Looper::_Looper() {
    mQueue = createMessageQueue();
}

void _Looper::quit() {
    mQueue->quit();
}

void _Looper::loop() {
    while(true) {
        auto msg = mQueue->next();
        if(msg != nullptr) {
            auto target = msg->getTarget();
            auto runnable = msg->getRunnable();
            if(runnable != nullptr) {
                runnable->run();
            } else {
                target->handleMessage(msg);
            }
            continue;
        }
        break;
    }
}

MessageQueue _Looper::getQueue() {
    return mQueue;
}

} // namespace obotcha
