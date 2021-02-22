#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "System.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Error.hpp"
#include "AutoLock.hpp"
#include "MethodNotSupportException.hpp"
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
    mIsShutDown = false;
    mIsTerminated = false;
    mStatusMutex = createMutex("statusMutex");
;
    mCachedExecutor = createExecutorBuilder()
                        ->setTimeout(60*1000)
                        ->newCachedThreadPool();
    
    mTaskMutex = createMutex("scheduleTaskMutex");
    mTaskWaitCond = createCondition();
    start();
}

int _ThreadScheduledPoolExecutor::shutdown() {
    {
        AutoLock l(mStatusMutex);
        
        if(mIsShutDown) {
            return -AlreadyDestroy;
        }

        mIsShutDown = true;
    }
    //clear all task
    {
        AutoLock l(mTaskMutex);
        WaitingTask task = mTaskPool;
        while(task != nullptr) {
            task->cancel();
            task = task->next;
        }
    }
    mTaskWaitCond->notify();
    mCachedExecutor->shutdown();
    return 0;
}

void _ThreadScheduledPoolExecutor::setAsTerminated() {
    //Do nothing
}

bool _ThreadScheduledPoolExecutor::isShutdown() {
    return mIsShutDown;
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

void _ThreadScheduledPoolExecutor::addWaitingTask(WaitingTask task) {
    AutoLock ll(mTaskMutex);
    if(mIsShutDown) {
        return;
    }
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
    while(1) {
        {
            AutoLock l(mStatusMutex);
            if(mIsShutDown) {
                return;
            }
        }
        WaitingTask mCurrentTask = nullptr;
        {
            AutoLock ll(mTaskMutex);
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
        }
        if(mCurrentTask->getStatus() == st(Future)::Cancel) {
            continue;
        }
        if(mCurrentTask != nullptr) {
            mCachedExecutor->submit(mCurrentTask->getRunnable());
        }
        mCurrentTask = nullptr;
    }
}

_ThreadScheduledPoolExecutor::~_ThreadScheduledPoolExecutor() { 
    
}

}
