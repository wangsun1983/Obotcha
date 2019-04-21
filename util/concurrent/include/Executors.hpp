#ifndef __EXECUTORS_HPP__
#define __EXECUTORS_HPP__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "ExecutorService.hpp"
#include "ScheduledExecutorService.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Executors) {

public:
    static ExecutorService newFixedThreadPool(int);
    static ExecutorService newSingleThreadExecutor();
    static ExecutorService newWorkStealingPool(int parallelism);
    static ExecutorService newWorkStealingPool();
    static ExecutorService newCachedThreadPool();
    static ScheduledExecutorService newSingleThreadScheduledExecutor();
    static ScheduledExecutorService newScheduledThreadPool();
};

}
#endif