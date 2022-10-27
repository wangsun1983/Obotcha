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

_WaitingTask::~_WaitingTask() {
    //nothing
}

//---------------ScheduleService---------------//
_ThreadScheduledPoolExecutor::_ThreadScheduledPoolExecutor(int maxPendingTaskNum,
                                                           uint32_t maxSubmitTaskWaitTime):_Executor() {
    mCachedExecutor =
        createExecutorBuilder()->newCachedThreadPool();

    mTaskMutex = createMutex();
    mCount = 0;
    mMaxPendingTaskNum = maxPendingTaskNum;
    mMaxSubmitTaskWaitTime = maxSubmitTaskWaitTime;
    
    //notEmpty = createCondition();
    notFull = createCondition();
    mTaskWaitCond = createCondition();
    mTaskPool = nullptr;
    mCurrentTask = nullptr;
    updateStatus(Executing);
    start();
}

int _ThreadScheduledPoolExecutor::shutdown() {
    if(isShutDown()) {
        return 0;
    }
    updateStatus(ShutDown);

    mCachedExecutor->shutdown();

    {
        AutoLock l(mTaskMutex);
        auto t = mTaskPool;
        while (mTaskPool != nullptr) {
            mTaskPool->cancel();
            auto header = mTaskPool;
            mTaskPool = mTaskPool->next;
            header->next = nullptr;
        }

        notFull->notify();
        //notEmpty->notify();
        mTaskWaitCond->notify();

        if(mCurrentTask != nullptr) {
            mCurrentTask->cancel();
        }

        mCurrentTask = nullptr;
    }

    return 0;
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

Future _ThreadScheduledPoolExecutor::submitRunnable(Runnable r) {
    WaitingTask task = createWaitingTask(r->getDelay(), r);
    return submitTask(task);
}

Future _ThreadScheduledPoolExecutor::submitTask(ExecutorTask task) {
    if(isShutDown()) {
        return nullptr;
    }

    task->setPending();
    if (addWaitingTaskLocked(Cast<WaitingTask>(task), mMaxSubmitTaskWaitTime) == 0) {
        return createFuture(task);
    }
    return nullptr;
}

int _ThreadScheduledPoolExecutor::addWaitingTaskLocked(WaitingTask task,
                                                       long timeout) {
    if(isShutDown()) {
        return -1;
    }

    AutoLock l(mTaskMutex);
    if (mMaxPendingTaskNum > 0 && mCount == mMaxPendingTaskNum) {
        if (notFull->wait(mTaskMutex, timeout) == -ETIMEDOUT) {
            return -1;
        }
    }

    if (mTaskPool == nullptr) {
        mTaskPool = task;
    } else {
        WaitingTask p = mTaskPool;
        WaitingTask prev = mTaskPool;
        for (;;) {
            //printf("p->nextTime is %ld,task->nextTime is %ld \n",p->nextTime,task->nextTime);
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
    //notEmpty->notify();
    mTaskWaitCond->notify();
    return 0;
}

void _ThreadScheduledPoolExecutor::run() {
    while (1) {
        if(isShutDown()) {
            return;
        }

        {
            AutoLock ll(mTaskMutex);
            if (mTaskPool == nullptr) {
                mTaskWaitCond->wait(mTaskMutex);
                continue;
            } else {
                long interval =
                    (mTaskPool->nextTime - st(System)::currentTimeMillis());
                //printf("interval is %d \n",interval);
                if (interval <= 0) {
                    mCurrentTask = mTaskPool;
                    mTaskPool = mTaskPool->next;
                    mCurrentTask->next = nullptr; //remove task link for stack overflow
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
            mCurrentTask = nullptr;
        }
    }
}

_ThreadScheduledPoolExecutor::~_ThreadScheduledPoolExecutor() {
    if(!isShutDown()) {
        LOG(ERROR)<<"ThreadScheduledPoolExecutor release without shutdown!!!!";
        close();
    }
}

void _ThreadScheduledPoolExecutor::close() {
    this->shutdown();
    this->awaitTermination();
}

} // namespace obotcha
