/**
 * @file Handler.cpp
 * @brief  A Thread that has a Looper. The Looper can then be used to 
 * create Handlers.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2023-01-17
 * @license none
 */

#include "HandlerThread.hpp"

namespace obotcha {

_HandlerThread::_HandlerThread() {
    mLooper = Looper::New();
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
