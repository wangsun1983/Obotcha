#include <stdio.h>
#include <stdlib.h>

#include "Executors.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ScheduledThreadPoolExecutor.hpp"
#include "ScheduledExecutorService.hpp"

namespace obotcha {

ExecutorService _Executors::newFixedThreadPool(int num) {
    return createThreadPoolExecutor(num);
}

ExecutorService _Executors::newSingleThreadExecutor() {
    return createThreadPoolExecutor(1);
}

ExecutorService _Executors::newWorkStealingPool(int parallelism) {
    //TODO
    return nullptr;
}

ExecutorService _Executors::newWorkStealingPool() {
    //TODO
    return nullptr;
}

ExecutorService _Executors::newCachedThreadPool() {
    //TODO
    return nullptr;
}

ScheduledExecutorService _Executors::newSingleThreadScheduledExecutor() {
    //TODO
    return nullptr;
}

ScheduledExecutorService _Executors::newScheduledThreadPool() {
    return createScheduledThreadPoolExecutor();
}


}