#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "ExecutorService.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"


namespace obotcha {

#define DEFAULT_CACHED_THREAD_WAIT_TIME 60*1000
#define DEFAULT_CACHED_THREAD_NUMS 32    

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   long timeout,
                                                                   _ThreadCachedPoolExecutor *h)
                                                                         :mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitIdle(false){
    mStateMutex = createMutex();
    mWaitCond = createCondition();

    mThread = createThread(this);
    
    mThreadTimeout = timeout;

    mThread->start();

    mPoolExecutor.set_pointer(h);
}

void _ThreadCachedPoolExecutorHandler::forceStop() {
    mThread->exit();
    //mPool->clear();
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(!mStop) {
        FutureTask task = mPool->deQueueFirst(mThreadTimeout);
        //no task,so we should remove this thread,and exit;
        if(task == nullptr) {
            mThread->exit();

            ThreadCachedPoolExecutorHandler t;
            t.set_pointer(this);
            mPoolExecutor->removeHandler(t);
            mPoolExecutor.remove_pointer();
            break;
        }

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

void _ThreadCachedPoolExecutorHandler::waitForIdle() {
    AutoMutex l(mStateMutex);
    isWaitIdle = true;
    if(mPool->size() != 0 || state != idleState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    mPool->clear();
}

bool _ThreadCachedPoolExecutorHandler::isIdle() {
    return state == idleState;
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int size,long timeout) {
    init(size,timeout);
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor() {
    init(DEFAULT_CACHED_THREAD_NUMS,DEFAULT_CACHED_THREAD_WAIT_TIME);
}

void _ThreadCachedPoolExecutor::shutdown(){

}

void _ThreadCachedPoolExecutor::shutdownNow() {

}

void _ThreadCachedPoolExecutor::execute(Runnable command) {

}

bool _ThreadCachedPoolExecutor::isShutdown() {

}

bool _ThreadCachedPoolExecutor::isTerminated() {

}

bool _ThreadCachedPoolExecutor::awaitTermination(long timeout) {

}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mIsShutDown) {
        return nullptr;//ExecuteResult::failShutDown;
    }

    if(mHandlers->size() == 0 || mPool->size()!= 0) {
        ThreadCachedPoolExecutorHandler t = createThreadCachedPoolExecutorHandler(mPool,mThreadTimeout,this);
        mHandlers->enQueueLast(t);
    } 

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);
    mPool->enQueueLast(task); 

    return future;   
}

void _ThreadCachedPoolExecutor::init(int size,long timeout) {
    mPool = createBlockingQueue<FutureTask>(size);
    mHandlers = createConcurrentQueue<ThreadCachedPoolExecutorHandler>();

    mIsTerminated = false;
    mIsShutDown = false;

    mPoolCapcity = size;

    mThreadTimeout = timeout;
}

void _ThreadCachedPoolExecutor::removeHandler(ThreadCachedPoolExecutorHandler h) {
    mHandlers->remove(h);
}

}
