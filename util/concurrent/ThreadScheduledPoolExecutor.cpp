#include <stdio.h>
#include <stdlib.h>

#include "AutoLock.hpp"
#include "Error.hpp"
#include "ExecutorBuilder.hpp"
#include "Log.hpp"
#include "System.hpp"
#include "Thread.hpp"
#include "ThreadScheduledPoolExecutor.hpp"

namespace obotcha {

//---------------WaitingTask---------------//
_WaitingTask::_WaitingTask(long int interval, Runnable r) : _ExecutorTask(r) {
    next = nullptr;
    nextTime = st(System)::currentTimeMillis() + interval;
}

//_WaitingTask::~WaitingTask() {
    //nothing
//}

//---------------ScheduleService---------------//
_ThreadScheduledPoolExecutor::_ThreadScheduledPoolExecutor(int capacity) {
    mCachedExecutor =
        createExecutorBuilder()->setTimeout(60 * 1000)->newCachedThreadPool();

    mTaskMutex = createMutex();
    mStatus = Executing;
    mCount = 0;
    mCapacity = capacity;
    notEmpty = createCondition();
    notFull = createCondition();
    mTaskWaitCond = createCondition();
    mTaskPool = nullptr;

    start();
}

int _ThreadScheduledPoolExecutor::shutdown() {
    printf("_ThreadScheduledPoolExecutor shutdown start \n");
    {
        AutoLock l(mTaskMutex);
        if (mStatus == ShutDown) {
            return -AlreadyDestroy;
        }

        mStatus = ShutDown;

        WaitingTask task = mTaskPool;
        while (task != nullptr) {
            task->cancel();
            task = task->next;
        }
        notFull->notify();
        notEmpty->notify();
        mTaskWaitCond->notify();
    }
    printf("_ThreadScheduledPoolExecutor shutdown trace1 \n");
    mCachedExecutor->shutdown();
    printf("_ThreadScheduledPoolExecutor shutdown trace2 \n");
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

int _ThreadScheduledPoolExecutor::addWaitingTaskLocked(WaitingTask task,
                                                       long timeout) {
    AutoLock l(mTaskMutex);
    if (mStatus == ShutDown) {
        return -1;
    }

    if (mCapacity > 0 && mCount == mCapacity) {
        if (notFull->wait(mTaskMutex, timeout) == -WaitTimeout) {
            return -1;
        }
    }

    if (mTaskPool == nullptr) {
        mTaskPool = task;
    } else {
        WaitingTask p = mTaskPool;
        WaitingTask prev = mTaskPool;
        for (;;) {
            if (p->nextTime > task->nextTime) {
                if (p == mTaskPool) {
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
                if (p == nullptr) {
                    prev->next = task;
                    break;
                }
            }
        }
    }

    mCount++;
    notEmpty->notify();
    return 0;
}

void _ThreadScheduledPoolExecutor::run() {
    WaitingTask mCurrentTask = nullptr;

    while (1) {
        {
            AutoLock ll(mTaskMutex);
            if (mStatus == ShutDown) {
                return;
            }

            if (mTaskPool == nullptr) {
                notEmpty->wait(mTaskMutex);
                continue;
            } else {
                long interval =
                    (mTaskPool->nextTime - st(System)::currentTimeMillis());
                if (interval <= 0) {
                    mCurrentTask = mTaskPool;
                    mTaskPool = mTaskPool->next;
                } else {
                    mTaskWaitCond->wait(mTaskMutex, interval);
                    continue;
                }
            }

            if (mCurrentTask->getStatus() == st(Future)::Cancel) {
                continue;
            }
        }

        mCachedExecutor->submitTask(mCurrentTask);
        {

            AutoLock l(mTaskMutex);
            notFull->notify();
            mCount--;
        }
        mCurrentTask = nullptr;
    }
}

_ThreadScheduledPoolExecutor::~_ThreadScheduledPoolExecutor() {}

void _ThreadScheduledPoolExecutor::close() {
    this->shutdown();
    this->awaitTermination();
}

} // namespace obotcha
