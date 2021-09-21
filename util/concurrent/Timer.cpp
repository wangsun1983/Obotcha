#include <stdio.h>

#include "ExecutorBuilder.hpp"
#include "System.hpp"
#include "Timer.hpp"

namespace obotcha {

ThreadScheduledPoolExecutor _Timer::mScheduledExecutor = nullptr;

_Timer::_Timer() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        mScheduledExecutor = createExecutorBuilder()->newScheduledThreadPool();
    });
}

Future _Timer::schedule(long m, Runnable r) {
    return mScheduledExecutor->submit(m, r);
}

Future _Timer::schedule(DateTime t, Runnable r) {
    long interval = t->millisecond() - st(System)::currentTimeMillis();
    if (interval < 0) {
        return nullptr;
    }
    return mScheduledExecutor->submit(interval, r);
}

_Timer::~_Timer() {
    // mScheduledExecutor->shutdown();
}

} // namespace obotcha