/**
 * @file Message.cpp
 * @brief Defines a message containing a description and arbitrary data 
 * object that can be sent to a Handler.  This object contains two extra 
 * int fields and an extra object field that allow you to not do allocations 
 * in many cases.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2023-01-17
 * @license none
 */
#include "Message.hpp"
#include "HandlerTarget.hpp"

namespace obotcha {

_Message::_Message(int w):what(w) {
}

_Message::_Message(Runnable r):mRunnable(r) {
}

void _Message::setTarget(sp<_HandlerTarget> cb) {
    mTarget = cb;
}

HandlerTarget _Message::getTarget() {
    return mTarget;
}

void _Message::setRunnable(Runnable r) {
    mRunnable = r;
}

void _Message::sendToTarget() {
    mTarget->sendMessage(AutoClone(this));
}

Runnable _Message::getRunnable() {
    return mRunnable;
}

} // namespace obotcha
