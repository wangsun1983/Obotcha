#include <stdio.h>

#include "Timer.hpp"
#include "System.hpp"

namespace obotcha {

_Timer::_Timer() {
    mScheduledExecutor = createThreadScheduledPoolExecutor();
}

void _Timer::schedule(Runnable r,long m) {
    mScheduledExecutor->schedule(m,r);
}

void _Timer::schedule(Runnable r,DateTime t) {
    long interval = t->millisecond() - st(System)::currentTimeMillis();
    if(interval < 0) {
        return;
    }
    mScheduledExecutor->schedule(interval,r);
}

_Timer::~_Timer() {
    mScheduledExecutor->shutdown();
}

}