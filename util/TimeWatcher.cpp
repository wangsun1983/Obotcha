#include "Object.hpp"
#include "StrongPointer.hpp"

#include "TimeWatcher.hpp"
#include "System.hpp"
#include "Log.hpp"

namespace obotcha {

_AutoTimeWatcher::_AutoTimeWatcher(String m) {
    mTag = m;
    current = st(System)::currentTimeMillis();
}

_AutoTimeWatcher::~_AutoTimeWatcher() {
    LOGD("AutoTimeWatcher",mTag," cost :",st(System)::currentTimeMillis() - current);
}


void _TimeWatcher::start() {
    current = st(System)::currentTimeMillis();
}

long _TimeWatcher::stop() {
    return st(System)::currentTimeMillis() - current;
}

}
