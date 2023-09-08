#include "TimeWatcher.hpp"

#include "Log.hpp"
#include "System.hpp"

namespace obotcha {

AutoTimeWatcher::AutoTimeWatcher(String m):mTag(m) {
    current = st(System)::CurrentTimeMillis();
}

AutoTimeWatcher::~AutoTimeWatcher() {
    LOG(INFO) << "AutoTimeWatcher" << mTag->toChars()
              << " cost :" << st(System)::CurrentTimeMillis() - current;
}

_TimeWatcher::_TimeWatcher() {
    start();
}

void _TimeWatcher::start() { 
    current = st(System)::CurrentTimeMillis(); 
}

long _TimeWatcher::stop() const { 
    return st(System)::CurrentTimeMillis() - current; 
}

} // namespace obotcha
