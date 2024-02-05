/**
 * @file TimeWatcher.cpp
 * @brief  The TimeWatcher class is an class that provides methods
 * to record how long function costs.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-15
 * @license none
 */

#include "TimeWatcher.hpp"

#include "Log.hpp"
#include "System.hpp"

namespace obotcha {

AutoTimeWatcher::AutoTimeWatcher(String m):mTag(m) {
    mCurrent = st(System)::CurrentTimeMillis();
}

AutoTimeWatcher::~AutoTimeWatcher() {
    LOG(INFO) << "AutoTimeWatcher" << mTag->toChars()
              << " cost :" << st(System)::CurrentTimeMillis() - mCurrent;
}

_TimeWatcher::_TimeWatcher() {
    start();
}

void _TimeWatcher::start() { 
    mCurrent = st(System)::CurrentTimeMillis(); 
}

long _TimeWatcher::stop() const { 
    return st(System)::CurrentTimeMillis() - mCurrent; 
}

} // namespace obotcha
