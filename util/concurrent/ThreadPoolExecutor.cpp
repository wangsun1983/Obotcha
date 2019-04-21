#include <stdio.h>
#include <stdlib.h>

#include "ExecutorService.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"

static int id = 0;

namespace obotcha {
_ThreadPoolExecutorHandler::_ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool):mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitIdle(false){
    mStateMutex = createMutex();
    mWaitCond = createCondition();

    mThread = createThread(this);
    
    //mThread->setName(createString(id));
    //id++;

    mThread->start();
}

void _ThreadPoolExecutorHandler::forceStop() {
    mThread->exit();
    mPool->clear();
}

void _ThreadPoolExecutorHandler::run() {
    while(!mStop) {
        FutureTask task = mPool->deQueueFirst();
        //printf("executor thred name is %s \n",mThread->getName()->toChars());
        {
            AutoMutex l(mStateMutex);
            state = busyState;
            if(task->getType() == FUTURE_TASK_SUBMIT) {
                task->onRunning();
            }
        }
        
        Runnable runnable = task->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }
     
        {
            AutoMutex l(mStateMutex);
            state = idleState;

            if(task->getType() == FUTURE_TASK_SUBMIT) {
                task->onComplete();
            }
        }
    }

    {
        AutoMutex l(mStateMutex);
        if(isWaitIdle) {
            //printf("notify trace \n");
            mWaitCond->notify();
            isWaitIdle = false;
        }
    }
}

void _ThreadPoolExecutorHandler::waitForIdle() {
    AutoMutex l(mStateMutex);
    isWaitIdle = true;
    if(mPool->size() != 0 || state != idleState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ThreadPoolExecutorHandler::stop() {
    mStop = true;
    mPool->clear();
}

bool _ThreadPoolExecutorHandler::isIdle() {
    return state == idleState;
}

_ThreadPoolExecutor::_ThreadPoolExecutor(int size) {
    init(size);
}

_ThreadPoolExecutor::_ThreadPoolExecutor() {
    init(1);
}

void _ThreadPoolExecutor::init(int size) {

    mPool = createBlockingQueue<FutureTask>(size);
    mHandlers = createConcurrentQueue<ThreadPoolExecutorHandler>();

    for(int i = 0; i < size;i++) {
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool);
        mHandlers->enQueueLast(h);
    }

    mIsTerminated = false;
    mIsShutDown = false;
}

void _ThreadPoolExecutor::execute(Runnable runnable) {
    if(mIsShutDown) {
        return;//ExecuteResult::failShutDown;
    }
    
    FutureTask task = createFutureTask(FUTURE_TASK_NORMAL,runnable);

    mPool->enQueueLast(task);
    //we should check mHandlers size
    //if(isDynamic) {
    //    if(mPool->size() != 0) {
    //        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool);           
    //        mHandlers->enQueueLast(h);
    //    }
    //}

    //return ExecuteResult::success;
}

void _ThreadPoolExecutor::shutdown() {
    mIsShutDown = true;
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->stop();
    }
}

void _ThreadPoolExecutor::shutdownNow() {
    mIsShutDown = true;
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->forceStop();
    }

    mIsTerminated = true;
}

Future _ThreadPoolExecutor::submit(Runnable r) {
    if(mIsShutDown) {
        return nullptr;//ExecuteResult::failShutDown;
    }
    
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);

    mPool->enQueueLast(task);

    return future;
}

bool _ThreadPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadPoolExecutor::isTerminated() {
    return false;
}

bool _ThreadPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return false;
    }

    if(millseconds == 0) {
        int size = mHandlers->size();
        for(int i = 0;i < size;i++) {
            mHandlers->get(i)->waitForIdle();
        }
        mIsTerminated = true;
        return true;
    } else {
        //TODO
    }

    return false;
}

}