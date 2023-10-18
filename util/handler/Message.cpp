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
