/**
 * @file Looper.cpp
 * @brief Class used to run a message loop for a thread.  Threads by default do
 * not have a message loop.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2023-01-17
 * @license none
 */
#include "Looper.hpp"

namespace obotcha {

_Looper::_Looper() {
    mQueue = MessageQueue::New();
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
