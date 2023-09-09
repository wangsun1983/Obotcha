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
