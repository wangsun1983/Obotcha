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
_WaitingTask::_WaitingTask(ExecutorTask task){
    next = nullptr;
    nextTime = st(System)::currentTimeMillis() + task->getDelay();
    this->task = task;
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
    printf("_ThreadScheduledPoolExecutor,mMaxPendingTaskNum is %d \n",mMaxPendingTaskNum);
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
            mTaskPool->task->cancel();
            auto header = mTaskPool;
            mTaskPool = mTaskPool->next;
            header->next = nullptr;
        }

        notFull->notify();
        //notEmpty->notify();
        mTaskWaitCond->notify();

        if(mCurrentTask != nullptr) {
            mCurrentTask->task->cancel();
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

int _ThreadScheduledPoolExecutor::getPendingTaskNum() {
    AutoLock l(mTaskMutex);
    return mCount;
}

int _ThreadScheduledPoolExecutor::getExecutingThreadNum() {
    return mCachedExecutor->getExecutingThreadNum();
}

Future _ThreadScheduledPoolExecutor::submitTask(ExecutorTask task) {
    if(isShutDown()) {
        return nullptr;
    }
    
    task->setPending();

    WaitingTask waitTask = createWaitingTask(task);

    if (addWaitingTaskLocked(waitTask, mMaxSubmitTaskWaitTime) == 0) {
        return createFuture(Cast<ExecutorTask>(waitTask));
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
    auto instance = AutoClone(this);
    while (1) {
        if(isShutDown()) {
            instance = nullptr;
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

            if (mCurrentTask->task->getStatus() == st(ExecutorTask)::Cancel) {
                continue;
            }
        }

        mCachedExecutor->submitTask(mCurrentTask->task);
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
