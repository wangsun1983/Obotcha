#include "Message.hpp"
#include "HandlerTarget.hpp"

namespace obotcha {

_Message::_Message() {
    nextTime = 0;
    next = nullptr;
    mRunnable = nullptr;
    what = -1;
}

_Message::_Message(int w):_Message() {
    what = w;
}

_Message::_Message(Runnable r):_Message() {
    mRunnable = r;
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

Runnable _Message::getRunnable() {
    return mRunnable;
}

} // namespace obotcha
