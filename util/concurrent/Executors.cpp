#include <stdio.h>
#include <stdlib.h>

#include "Executors.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "ScheduledExecutorService.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "ThreadPriorityPoolExecutor.hpp"

namespace obotcha {

//ExecutorRecyler
Mutex _ExecutorRecyler::mMutex = createMutex("exerecylermutex");
ExecutorRecyler _ExecutorRecyler::mInstance = nullptr;

_ExecutorRecyler::_ExecutorRecyler() {
    mRecyleList = createLinkedList<ExecutorService>();
    mCond = createCondition();
}

sp<_ExecutorRecyler>_ExecutorRecyler::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }
    AutoLock l(mMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _ExecutorRecyler *p = new _ExecutorRecyler();
    p->detach();
    p->start();
    mInstance.set_pointer(p);
    return mInstance;
}

void _ExecutorRecyler::run() {
    while(1) {
        ExecutorService service = nullptr;
        {
            AutoLock l(mMutex);
            if(mRecyleList->isEmpty()) {
                mCond->wait(mMutex);
            }
        
            service = mRecyleList->deQueueFirst();
        }
        
        if(service->awaitTermination(1000) != 0) {
            AutoLock l(mMutex);
            mRecyleList->enQueueLast(service);
        }
    }
}

void _ExecutorRecyler::add(ExecutorService s) {
    AutoLock l(mMutex);
    mRecyleList->enQueueLast(s);
    mCond->notify();
}

//_Executors
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

ExecutorService _Executors::newPriorityThreadPool(int thread_num) {
    return createThreadPriorityPoolExecutor(thread_num);
}

ExecutorService _Executors::newPriorityThreadPool(){
    return createThreadPriorityPoolExecutor();
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
    return createThreadScheduledPoolExecutor();
}


}