#include <stdio.h>
#include <stdlib.h>

#include "Executors.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ScheduledThreadPoolExecutor.hpp"
#include "ScheduledExecutorService.hpp"
#include "ThreadCachedPoolExecutor.hpp"

namespace obotcha {

ExecutorService _Executors::newFixedThreadPool(int queue_size,int thread_num) {
    return createThreadPoolExecutor(queue_size,thread_num);
}

ExecutorService _Executors::newFixedThreadPool(int thread_num) {
    return createThreadPoolExecutor(-1,thread_num);
}

ExecutorService _Executors::newSingleThreadExecutor(int queue_size) {
    return createThreadPoolExecutor(queue_size,1);
}

ExecutorService _Executors::newWorkStealingPool(int parallelism) {
    //TODO
    return nullptr;
}

ExecutorService _Executors::newWorkStealingPool() {
    //TODO
    return nullptr;
}

ExecutorService _Executors::newCachedThreadPool(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    return createThreadCachedPoolExecutor(queuesize,minthreadnum,maxthreadnum,timeout);
}

ExecutorService _Executors::newCachedThreadPool(int maxthreadnum,long timeout) {
    return createThreadCachedPoolExecutor(maxthreadnum,timeout);
}

ExecutorService _Executors::newCachedThreadPool() {
    return createThreadCachedPoolExecutor();
}

ScheduledExecutorService _Executors::newSingleThreadScheduledExecutor() {
    //TODO
    return nullptr;
}

ScheduledExecutorService _Executors::newScheduledThreadPool() {
    return createScheduledThreadPoolExecutor();
}


}