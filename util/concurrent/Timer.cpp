#include <stdio.h>

#include "Timer.hpp"
#include "System.hpp"

namespace obotcha {

_Timer::_Timer() {
    mScheduledExecutor = createScheduledThreadPoolExecutor();
}

void _Timer::schedule(Runnable r,long m) {
    mScheduledExecutor->schedule(r,m);
}

void _Timer::schedule(Runnable r,DateTime t) {
    long interval = t->millisecond() - st(System)::currentTimeMillis();
    if(interval < 0) {
        return;
    }
    mScheduledExecutor->schedule(r,interval);
}

_Timer::~_Timer() {
    mScheduledExecutor->shutdown();
}

}