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
        if(auto msg = mQueue->next();msg != nullptr) {
            auto target = msg->getTarget();
            if(auto runnable = msg->getRunnable();runnable != nullptr) {
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
