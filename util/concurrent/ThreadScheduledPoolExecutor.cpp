#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "System.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Error.hpp"
#include "AutoLock.hpp"
#include "MethodNotSupportException.hpp"
#include "Log.hpp"

namespace obotcha {

//---------------WaitingTask---------------//
_WaitingTask::_WaitingTask(Runnable r):_FutureTask(r) {
    //nothing
    next = nullptr;
}

void _WaitingTask::setExecutor(_ThreadScheduledPoolExecutor *p) {
    mExecutor = p;
}

void _WaitingTask::init(long int interval,int type,int repeat) {
    nextTime = st(System)::currentTimeMillis() + interval;
    mScheduleTaskType = type;
    repeatDelay = repeat;
}

void _WaitingTask::onComplete() {
    switch(mScheduleTaskType) {
        case ScheduletTaskNormal:
        case ScheduletTaskFixRate:
        //Do nothing
        break;

        case ScheduletTaskFixedDelay: {
            WaitingTask task = AutoClone(this);
            task->nextTime = (st(System)::currentTimeMillis() + task->repeatDelay);
            mExecutor->addWaitingTask(task);
        }
        break;
    }
    st(FutureTask)::onComplete();
}

//---------------ScheduleService---------------//
_ThreadScheduledPoolExecutor::_ThreadScheduledPoolExecutor() {
    mIsShutDown = false;
    mIsTerminated = false;
    mStatusMutex = createMutex("statusMutex");

    int cpuNum = st(System)::availableProcessors();
    mCachedExecutor = createThreadCachedPoolExecutor(cpuNum*4,60*1000);
    
    mTaskMutex = createMutex("scheduleTaskMutex");
    mTaskWaitCond = createCondition();
    start();
}


int _ThreadScheduledPoolExecutor::getThreadsNum() {
    Trigger(MethodNotSupportException,"getThreadsNum not support");
    return 0;
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
            }else if(mTaskPool != nullptr) {
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

        int interval = mCurrentTask->nextTime - st(System)::currentTimeMillis();
        if(interval <= 0) {
            mCachedExecutor->submit((FutureTask)mCurrentTask);
            if(mCurrentTask->mScheduleTaskType == ScheduletTaskFixRate) {
                mCurrentTask->nextTime = (st(System)::currentTimeMillis() + mCurrentTask->repeatDelay);
                addWaitingTask(mCurrentTask);
            }
        } else {
            int ret = mTaskWaitCond->wait(mTaskMutex,interval);
            if(ret != -WaitTimeout) {
                addWaitingTask(mCurrentTask);
            }
        }

        mCurrentTask = nullptr;
    }
}

_ThreadScheduledPoolExecutor::~_ThreadScheduledPoolExecutor() { 
    
}

}
