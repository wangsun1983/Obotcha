#include "TimeWatcher.hpp"

#include "Log.hpp"
#include "System.hpp"

namespace obotcha {

_AutoTimeWatcher::_AutoTimeWatcher(String m):mTag(m) {
    current = st(System)::CurrentTimeMillis();
}

_AutoTimeWatcher::~_AutoTimeWatcher() {
    LOG(INFO) << "AutoTimeWatcher" << mTag->toChars()
              << " cost :" << st(System)::CurrentTimeMillis() - current;
}

void _TimeWatcher::start() { 
    current = st(System)::CurrentTimeMillis(); 
}

long _TimeWatcher::stop() const { 
    return st(System)::CurrentTimeMillis() - current; 
}

} // namespace obotcha
