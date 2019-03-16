#include <stdio.h>
#include <stdlib.h>

#include "ExecutorService.hpp"
#include "Thread.hpp"

namespace obotcha {
_ExecutorServiceHandler::_ExecutorServiceHandler(BlockingQueue<Runnable> pool):mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitIdle(false){
    mStateMutex = createMutex();
    mWaitCond = createCondition();

    mThread = createThread(this);
    mThread->start();
}

void _ExecutorServiceHandler::run() {
    while(!mStop) {
        Runnable runnable = mPool->deQueueFirst();

        {
            AutoMutex l(mStateMutex);
            state = busyState;
        }

        runnable->run();
     
        {
            AutoMutex l(mStateMutex);
            state = idleState;
        }

        if(mPool->size() == 0) {
            if(isWaitIdle) {
                printf("notify trace \n");
                mWaitCond->notify();
                isWaitIdle = false;
            }
        }
    }
}

void _ExecutorServiceHandler::waitForIdle() {
    AutoMutex l(mStateMutex);
    isWaitIdle = true;
    if(mPool->size() != 0 || state != idleState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ExecutorServiceHandler::stop() {
    mStop = true;
}

bool _ExecutorServiceHandler::isIdle() {
    return state == idleState;
}

_ExecutorService::_ExecutorService(int size) {
    init(size,false);
}

_ExecutorService::_ExecutorService() {
    init(-1,true);
}

void _ExecutorService::init(int size,bool isDyn) {

    mPool = createBlockingQueue<Runnable>(size);
    mHandlers = createConcurrentQueue<ExecutorServiceHandler>();

    for(int i = 0; i < size;i++) {
        ExecutorServiceHandler h = createExecutorServiceHandler(mPool);
        mHandlers->enQueueLast(h);
    }

    isDynamic = isDyn;
}

int _ExecutorService::execute(Runnable runnable) {
    if(isShutDown) {
        return ExecuteResult::failShutDown;
    }
    
    mPool->enQueueLast(runnable);
    //we should check mHandlers size
    if(isDynamic) {
        if(mPool->size() != 0) {
            ExecutorServiceHandler h = createExecutorServiceHandler(mPool);           
            mHandlers->enQueueLast(h);
        }
    }

    return ExecuteResult::success;
}

void _ExecutorService::shutdown() {
    //TODO
}

void _ExecutorService::awaitTermination() {
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->waitForIdle();
    }
}

void _ExecutorService::awaitTermination(long millseconds) {
    //TODO
}

}