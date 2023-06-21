#include "HandlerThread.hpp"

namespace obotcha {

_HandlerThread::_HandlerThread() {
    mLooper = createLooper();
}

void  _HandlerThread::run() {
    mLooper->loop();
}

void _HandlerThread::quit() {
    mLooper->quit();
}

Looper _HandlerThread::getLooper() {
    return mLooper;
}

} // namespace obotcha
