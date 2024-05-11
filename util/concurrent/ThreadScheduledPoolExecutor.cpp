#include "ThreadScheduledPoolExecutor.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "ExecutorBuilder.hpp"
#include "Log.hpp"
#include "System.hpp"
#include "Inspect.hpp"

namespace obotcha {

//---------------WaitingTask---------------//
_WaitingTask::_WaitingTask(ExecutorTask tsk):task(tsk){
    nextTime = st(System)::CurrentTimeMillis() + tsk->getDelay();
}

//---------------ScheduleService---------------//
_ThreadScheduledPoolExecutor::_ThreadScheduledPoolExecutor(size_t maxPendingTaskNum,
                                                           uint32_t maxSubmitTaskWaitTime):_Executor() {
    mCachedExecutor = ExecutorBuilder::New()->newCachedThreadPool();
    mMaxPendingTaskNum = maxPendingTaskNum;
    mMaxSubmitTaskWaitTime = maxSubmitTaskWaitTime;    
    updateStatus(st(Concurrent)::Status::Running);
    start();
}

int _ThreadScheduledPoolExecutor::shutdown() {
    Inspect(isShutDown(),0)
    updateStatus(st(Concurrent)::Status::ShutDown);
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

int _ThreadScheduledPoolExecutor::awaitTermination(long timeout) {
    return mCachedExecutor->awaitTermination(timeout);
}

size_t _ThreadScheduledPoolExecutor::getPendingTaskNum() {
    AutoLock l(mTaskMutex);
    return mCount;
}

size_t _ThreadScheduledPoolExecutor::getExecutingThreadNum() {
    return mCachedExecutor->getExecutingThreadNum();
}

Future _ThreadScheduledPoolExecutor::submitTask(ExecutorTask task) {
    Inspect(isShutDown(),nullptr)
    WaitingTask waitTask = WaitingTask::New(task);
    if (addWaitingTaskLocked(waitTask, mMaxSubmitTaskWaitTime) == 0) {
        task->setPending();
        return Future::New(task);
    }
    return nullptr;
}

int _ThreadScheduledPoolExecutor::addWaitingTaskLocked(WaitingTask task,
                                                       long timeout) {
    Inspect(isShutDown(),-1)

    while(true) {
        AutoLock l(mTaskMutex);
        if (mMaxPendingTaskNum > 0 && mCount == mMaxPendingTaskNum) {
            int result = notFull->wait(mTaskMutex, timeout);
            if(result < 0) return result;
            continue;
        }
        break;
    }

    AutoLock l(mTaskMutex);
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
    mTaskWaitCond->notify();
    return 0;
}

void _ThreadScheduledPoolExecutor::run() {
    auto instance = AutoClone(this);
    while(true) {
        Inspect(isShutDown())
        {
            AutoLock ll(mTaskMutex);
            if (mTaskPool == nullptr) {
                mTaskWaitCond->wait(mTaskMutex);
                continue;
            } else {
                long interval =
                    (mTaskPool->nextTime - st(System)::CurrentTimeMillis());
                if (interval <= 0) {
                    mCurrentTask = mTaskPool;
                    mTaskPool = mTaskPool->next;
                    //remove task link for stack overflow
                    mCurrentTask->next = nullptr; 
                } else {
                    mTaskWaitCond->wait(mTaskMutex, interval);
                    continue;
                }
            }

            if (mCurrentTask->task->getStatus() == st(Concurrent)::Status::Interrupt) {
                mCount--;
                continue;
            }
        }

        mCachedExecutor->submitTask(mCurrentTask->task);

        {
            AutoLock l(mTaskMutex);
            if(notFull->getWaitCount() != 0) notFull->notify();
            mCount--;
            mCurrentTask = nullptr;
        }
    }
}

void _ThreadScheduledPoolExecutor::onRemoveTask(ExecutorTask task) {
    Inspect(!isExecuting())
    
    AutoLock l(mTaskMutex);
    auto current = mTaskPool;
    auto prev = mTaskPool;

    while (current != nullptr) {
        if(current->task == task) {
            if(current == mTaskPool) {
                mTaskPool = mTaskPool->next;
                current->next = nullptr;
            } else {
                prev->next = current->next;
            }
            break;
        } else {
            prev = current;
            current = current->next;
        }
    }

    mCachedExecutor->onRemoveTask(task);
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
