#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "System.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Error.hpp"
#include "AutoLock.hpp"
#include "ExecutorBuilder.hpp"
#include "Log.hpp"

namespace obotcha {

//---------------WaitingTask---------------//
_WaitingTask::_WaitingTask(long int interval,Runnable r):_FutureTask(r) {
    //nothing
    next = nullptr;
    nextTime = st(System)::currentTimeMillis() + interval;
}

//---------------ScheduleService---------------//
_ThreadScheduledPoolExecutor::_ThreadScheduledPoolExecutor() {
    mCachedExecutor = createExecutorBuilder()
                        ->setTimeout(60*1000)
                        ->newCachedThreadPool();
    
    mTaskMutex = createMutex("scheduleTaskMutex");
    mTaskWaitCond = createCondition();
    mStatus = Running;
    start();
}

int _ThreadScheduledPoolExecutor::shutdown() {
    {
        AutoLock l(mTaskMutex);
        if(mStatus == ShutDown) {
            return -AlreadyDestroy;
        }

        mStatus = ShutDown;

        WaitingTask task = mTaskPool;
        while(task != nullptr) {
            task->cancel();
            task = task->next;
        }
        mTaskWaitCond->notify();
    }

    mCachedExecutor->shutdown();
    return 0;
}

bool _ThreadScheduledPoolExecutor::isShutdown() {
    AutoLock l(mTaskMutex);
    return mStatus == ShutDown;
}

bool _ThreadScheduledPoolExecutor::isTerminated() {
    return mCachedExecutor->isTerminated();
}

void _ThreadScheduledPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadScheduledPoolExecutor::awaitTermination(long timeout) {
    return mCachedExecutor->awaitTermination(timeout);
}

void _ThreadScheduledPoolExecutor::addWaitingTaskLocked(WaitingTask task) {
    if(mTaskPool == nullptr) {
        mTaskPool = task;
    } else {
        WaitingTask p = mTaskPool;
        WaitingTask prev = mTaskPool;
        for (;;) {
            if(p->nextTime > task->nextTime) {
                if(p == mTaskPool) {
                    task->next = p;
                    mTaskPool = task;
                } else {
                    prev->next = task;
                    task->next = p;
                }
                break;
            } else {
                prev = p;
                p = p->next;
                if(p == nullptr) {
                    prev->next = task;
                    break;
                }
            }
        }
    }
    mTaskWaitCond->notify();
}

void _ThreadScheduledPoolExecutor::run() {
    WaitingTask mCurrentTask = nullptr;

    while(1) {
        {
            AutoLock ll(mTaskMutex);
            if(mStatus == ShutDown) {
                return;
            }
            
            if(mTaskPool == nullptr) {
                mTaskWaitCond->wait(mTaskMutex);
                continue;
            }else {
                long interval = (mTaskPool->nextTime - st(System)::currentTimeMillis());
                if(interval <= 0) {
                    mCurrentTask = mTaskPool;
                    mTaskPool = mTaskPool->next;
                } else {
                    mTaskWaitCond->wait(mTaskMutex,interval);
                    continue;
                }
            }
            
            if(mCurrentTask->getStatus() == st(Future)::Cancel) {
                continue;
            }
        }

        mCachedExecutor->submit(mCurrentTask->getRunnable());        
        mCurrentTask = nullptr;
    }
}

_ThreadScheduledPoolExecutor::~_ThreadScheduledPoolExecutor() { 
    
}

}
