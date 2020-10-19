#ifndef __OBOTCHA_EXECUTORS_HPP__
#define __OBOTCHA_EXECUTORS_HPP__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "ExecutorService.hpp"
#include "ScheduledExecutorService.hpp"
#include "LinkedList.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ExecutorRecyler) IMPLEMENTS(Thread){

public:
    static sp<_ExecutorRecyler>getInstance();
    void add(ExecutorService);

private:
    _ExecutorRecyler();
    void run();
    static ExecutorRecyler mInstance;
    static Mutex mMutex;
    Condition mCond;
    LinkedList<ExecutorService> mRecyleList;
};

DECLARE_SIMPLE_CLASS(Executors) {

public:
    static ExecutorService newFixedThreadPool(int queue_size,int thread_num);
    static ExecutorService newFixedThreadPool(int thread_num);

    static ExecutorService newSingleThreadExecutor(int queue_size);
    static ExecutorService newWorkStealingPool(int parallelism);
    static ExecutorService newWorkStealingPool();
    
    static ExecutorService newCachedThreadPool(int queue_size,int maxthreadnum,int minthreadnum,long timeout);
    static ExecutorService newCachedThreadPool(int maxthreadnum,long timeout);
    static ExecutorService newCachedThreadPool();


    static ScheduledExecutorService newSingleThreadScheduledExecutor();
    static ScheduledExecutorService newScheduledThreadPool();

    static ExecutorService newPriorityThreadPool(int thread_num);
    static ExecutorService newPriorityThreadPool();
    
};

}
#endif