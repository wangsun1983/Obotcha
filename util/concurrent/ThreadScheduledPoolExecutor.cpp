#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "System.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Error.hpp"
#include "AutoLock.hpp"
#include "MethodNotSupportException.hpp"
#include "ExecutorDestructorException.hpp"
#include "Log.hpp"

namespace obotcha {

//---------------WaitingTask---------------//
_WaitingTask::_WaitingTask(int type,Runnable r):_FutureTask(type,r) {
    //nothing
}

_WaitingTask::_WaitingTask(int type,Runnable r,FutureTaskStatusListener l):_FutureTask(type,r,l) {
    //nothing
}

void _WaitingTask::setExecutor(_ThreadScheduledPoolExecutor *p) {
    mExecutor = p;
}

void _WaitingTask::init(long int interval,int type,int repeat) {
    mNextTime = st(System)::currentTimeMillis() + interval;
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
            WaitingTask task;
            task.set_pointer(this);
            task->mNextTime = (st(System)::currentTimeMillis() + task->repeatDelay);
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
}

int _ThreadScheduledPoolExecutor::execute(Runnable runnable) {
    
    if(submit(runnable) == nullptr) {
        return -InvalidStatus;
    }

    return 0;
}

int _ThreadScheduledPoolExecutor::getThreadsNum() {
    throw MethodNotSupportException(createString("getThreadsNum not support"));
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
    AutoLock l(mTaskMutex);
    while(1) {
        WaitingTask task = getWaitingTask();
        if(task == nullptr) {
            break;
        }

        task->onShutDown();
    }
    mTaskWaitCond->notify();

    return 0;
}

bool _ThreadScheduledPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadScheduledPoolExecutor::isTerminated() {
    //return mTimeThread->isTerminated;
    return mCachedExecutor->isTerminated();
}

void _ThreadScheduledPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadScheduledPoolExecutor::awaitTermination(long timeout) {
    return mCachedExecutor->awaitTermination(timeout);
}

Future _ThreadScheduledPoolExecutor::submit(Runnable r) {
    {
        AutoLock l(mStatusMutex);

        if(mIsShutDown) {
            return nullptr;
        }
    }

    return schedule(r,0);
}

Future _ThreadScheduledPoolExecutor::schedule(Runnable r,long delay) {
    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    WaitingTask task = createWaitingTask(FUTURE_TASK_SUBMIT,r,listener);
    task->init(delay,ScheduletTaskNormal,-1);
    task->setExecutor(this);

    Future future = createFuture(task);
    return future;
}

Future _ThreadScheduledPoolExecutor::scheduleAtFixedRate(Runnable r,
                                long initialDelay,
                                long period) {

    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    WaitingTask task = createWaitingTask(FUTURE_TASK_SUBMIT,r,listener);
    task->init(initialDelay,ScheduletTaskFixRate,period);
    task->setExecutor(this);

    Future future = createFuture(task);
    return future;
}

Future _ThreadScheduledPoolExecutor::scheduleWithFixedDelay(Runnable r,
                                long initialDelay,
                                long delay) {

    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    WaitingTask task = createWaitingTask(FUTURE_TASK_SUBMIT,r,listener);
    task->init(initialDelay,ScheduletTaskFixedDelay,delay);

    Future future = createFuture(task);
    return future;
}

WaitingTask _ThreadScheduledPoolExecutor::getWaitingTask() {
    AutoLock ll(mTaskMutex);
    WaitingTask task = mRoot;
    if(task == nullptr) {
        return nullptr;
    }

    while(1) {
        if(task->left == nullptr) {
            break;
        }
        task = task->left;
    }
    
    if(task->parent == nullptr) {
        //this is a Root
        mRoot == task->right;
        return task;
    }

    task->parent->left = task->right;
    if(task->right != nullptr) {
        task->right->parent = task->parent;
    }

    return task;
}

void _ThreadScheduledPoolExecutor::addWaitingTask(WaitingTask t) {
    AutoLock ll(mTaskMutex);
    if(mIsShutDown) {
        return;
    }

    if(mRoot == nullptr) {
        mRoot = t;
        return;
    }

    WaitingTask task = mRoot;
    while(1) {
        if(t->mNextTime <= task->mNextTime) {
            if(task->left == nullptr) {
                task->left = t;
                t->parent = task;
                break;
            } 
            task = task->left;
            continue;
        }

        if(t->mNextTime > task->mNextTime) {
            if(task->right == nullptr) {
                task->right = t;
                t->parent = task;
            }
            task = task->right;
            continue;
        }
    }
    
    mTaskWaitCond->notify();
}

//called from Future->cancel
void _ThreadScheduledPoolExecutor::onCancel(FutureTask task) {
    mCachedExecutor->onCancel(task);
}

void _ThreadScheduledPoolExecutor::run() {
    while(1) {
        {
            AutoLock l(mStatusMutex);
            if(mIsShutDown) {
                return;
            }
        }

        AutoLock ll(mTaskMutex);
        WaitingTask waitingTask = getWaitingTask();
        if(waitingTask == nullptr) {
            mTaskWaitCond->wait(mTaskMutex);
            continue;
        }

        if(waitingTask->getStatus() == st(Future)::Cancel) {
            continue;
        }

        int interval = waitingTask->mNextTime - st(System)::currentTimeMillis();
        if(interval <= 0) {
            mCachedExecutor->submit((FutureTask)waitingTask);
            if(waitingTask->mScheduleTaskType == ScheduletTaskFixRate) {
                waitingTask->mNextTime = (st(System)::currentTimeMillis() + waitingTask->repeatDelay);
                addWaitingTask(waitingTask);
            }
        } else {
            int ret = mTaskWaitCond->wait(mTaskMutex,interval);
            if(ret != -WaitTimeout) {
                addWaitingTask(waitingTask);
            }
        }
    }
}

_ThreadScheduledPoolExecutor::~_ThreadScheduledPoolExecutor() { 
    
}

}
