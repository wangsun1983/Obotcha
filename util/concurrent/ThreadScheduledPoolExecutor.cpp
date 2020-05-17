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

#define TAG "ScheduledThreadPool"

//---------------ScheduledTaskWorker-------------------//
_ScheduledTaskWorker::_ScheduledTaskWorker(sp<_WaitingTask> t,ScheduledThreadPoolThread thread) {
    mTask = t;
    mTimeThread = thread;
}

_ScheduledTaskWorker::~_ScheduledTaskWorker() {
    mTimeThread.remove_pointer();
}

void _ScheduledTaskWorker::onInterrupt() {
    
    Runnable r = nullptr;
    if(mTask != nullptr) {
        r = mTask->task->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
    }

    if(mTimeThread != nullptr && r != nullptr) {
        mTimeThread->onTaskFinished(r);
        mTimeThread.remove_pointer();
    }
}

void _ScheduledTaskWorker::run() {
    long int startMillseconds = 0;

    if(mTask->mScheduleTaskType == ScheduletTaskFixRate) {
        startMillseconds = st(System)::currentTimeMillis();
    }

    Runnable runnable = mTask->task->getRunnable();
    if(runnable != nullptr) {
        runnable->run();    
    }

    //we should check the whether the Task is a repeated task;
    switch(mTask->mScheduleTaskType) {
        case ScheduletTaskFixRate: {
            long internal = st(System)::currentTimeMillis() - startMillseconds;
            if(mTask->repeatDelay > internal) {
                mTask->mNextTime = st(System)::currentTimeMillis() + (mTask->repeatDelay - internal);
            } else {
                mTask->mNextTime = st(System)::currentTimeMillis();
            }
            
            mTimeThread->addTask(mTask);
        }
        break;

        case ScheduletTaskFixedDelay: {
            long int current = st(System)::currentTimeMillis();
            mTask->mNextTime = current + mTask->repeatDelay;
            mTimeThread->addTask(mTask);
        }
        break;

        case ScheduletTaskNormal: {
            if(mTimeThread != nullptr) {
                mTimeThread->onTaskFinished(runnable);
                mTimeThread.remove_pointer();
            }
        }
        break;
    }
}

//---------------WaitingTask---------------//
_WaitingTask::_WaitingTask(FutureTask t,long int interval) {
    task = t;
    mNextTime = st(System)::currentTimeMillis() + interval;
    mScheduleTaskType = ScheduletTaskNormal;
}

_WaitingTask::_WaitingTask(FutureTask t,
                           long int interval,
                           int type,
                           long int delay) {
    task = t;
    mNextTime = st(System)::currentTimeMillis() + interval;
    mScheduleTaskType = type;
    repeatDelay = delay;
}

_WaitingTask::~_WaitingTask() {
    task = nullptr;
    mTimeThread.remove_pointer();
}


//---------------TimeThread---------------//
_ScheduledThreadPoolThread::_ScheduledThreadPoolThread(ThreadCachedPoolExecutor m) {
    mWaitingTasks = createArrayList<WaitingTask>();

    mDataLock = createMutex("ScheduledThreadPoolDataMutex");
    mDataCond = createCondition();

    mTimeLock = createMutex("ScheduledThreadPoolTimeMutex");
    mTimeCond = createCondition();

    mTerminatedMutex = createMutex("ScheduledThreadPoolTermMutex");
    mTerminatedCond = createCondition();

    mFuturesMutex = createMutex("ScheduledThreadPoolFutureMutex");
    mFutures = createHashMap<Runnable,Future>();
    
    mTaskMutex = createMutex("ScheduledTaskMutex");
    mCurrentTask = nullptr;

    cachedExecutor = m;

    isStop = false;
    isTerminated = false;
}

_ScheduledThreadPoolThread::~_ScheduledThreadPoolThread() {
    {
        AutoLock ll(mFuturesMutex);
        mFutures->clear();
    }
}

void _ScheduledThreadPoolThread::onUpdate() {
    mDataCond->notify();
    mTimeCond->notify();
}

void _ScheduledThreadPoolThread::addTask(WaitingTask v) {
    AutoLock l(mDataLock);
    int start = 0;
    int end = mWaitingTasks->size() - 1;
    int index = 0;
    while(start <= end) {
        index = (start+end)/2;
        WaitingTask m = mWaitingTasks->get(index);
        if(m->mNextTime > v->mNextTime) {
            end = index - 1;
        } else if(m->mNextTime < v->mNextTime) {
            start = index + 1;
        } else if(m->mNextTime == v->mNextTime) {
            break;
        }
    }

    mWaitingTasks->insert(index,v);

    onUpdate();
}

void _ScheduledThreadPoolThread::stop() {
    this->quit();
    cachedExecutor->shutdown();
}

void _ScheduledThreadPoolThread::waitForTerminate() {
    waitForTerminate(0);
}

void _ScheduledThreadPoolThread::waitForTerminate(long timeout) {
    if(isTerminated) {
        return;
    }

    AutoLock l(mTerminatedMutex);

    if(!isTerminated) {
        if(timeout == 0) {
            mTerminatedCond->wait(mTerminatedMutex);
        } else {
            mTerminatedCond->wait(mTerminatedMutex,timeout);
        }
    }
}

void _ScheduledThreadPoolThread::onInterrupt() {
    //CachedExector will clear mCurrentTask's runnable;
    {
        AutoLock l(mTerminatedMutex);
        isTerminated = true;
        mTerminatedCond->notify();
    }
    
    //clear all task
    {
        AutoLock l(mTaskMutex);
        if(mCurrentTask != nullptr) {
            if(mCurrentTask->task != nullptr) {
                mCurrentTask->task->cancel();
            }
        }
        mCurrentTask = nullptr;
    }

    {
        AutoLock ll(mDataLock);
        ListIterator<WaitingTask> iterator = mWaitingTasks->getIterator();
        while(iterator->hasValue()) {
            WaitingTask t = iterator->getValue();
            if(t != nullptr) {
                t->task->cancel();
            }
            iterator->next();
        }
        mWaitingTasks->clear();
    }
}

void _ScheduledThreadPoolThread::stopTask(FutureTask task) {
    {
        AutoLock l(mDataLock);

        ListIterator<WaitingTask> iterator = mWaitingTasks->getIterator();
        WaitingTask t = nullptr;
        while(iterator->hasValue()) {
            t = iterator->getValue();
            if(t->task == task) {
                mWaitingTasks->remove(t);
                return;
            }
            iterator->next();
        }
    }
    
    {
        Runnable r = task->getRunnable();
        AutoLock ll(mFuturesMutex);
        Future f = mFutures->get(r);
        if(f != nullptr) {
            f->cancel();
        } else if(task == mCurrentTask) {
            mCurrentTask->task->cancel();
        }
        mFutures->remove(r);
    }
}

void _ScheduledThreadPoolThread::onTaskFinished(Runnable r) {
    {
        AutoLock ll(mFuturesMutex);
        mFutures->remove(r);
    }
}

void _ScheduledThreadPoolThread::run() {
    while(!isStop) {
        st(Thread)::interruptCheck();
        {
            AutoLock l(mTaskMutex);
            mCurrentTask = nullptr;
        }

        {
            AutoLock l(mDataLock);
            while(1) {
                if(isStop) {
                    goto end;
                }

                if(mWaitingTasks->size() == 0) {
                    mDataCond->wait(mDataLock);
                    continue;
                }
                mCurrentTask = mWaitingTasks->get(0);
                break;
            }
         
            //get first time to wait;
            long currentTime = st(System)::currentTimeMillis();
            long interval = mCurrentTask->mNextTime - currentTime;
            if(interval > 0) {
                mTimeCond->wait(mDataLock,interval);
                continue;
            } else {
                {
                    if(mWaitingTasks->remove(mCurrentTask) < 0) {
                        continue;
                    }
                }
            }
        }

        if(mCurrentTask->task->getStatus() == st(Future)::Cancel) {
            continue;
        }

        Runnable r = mCurrentTask->task->getRunnable();
        if(r != nullptr) {
            ScheduledThreadPoolThread t;
            t.set_pointer(this);
            printf("thread scheduled add one task \n");
            ScheduledTaskWorker worker = createScheduledTaskWorker(mCurrentTask,t);
            Future future = cachedExecutor->submit(worker);
            {
                AutoLock ll(mFuturesMutex);
                mFutures->put(r,future);
            }
        }
    }

end:
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoLock l(mTaskMutex);
        mCurrentTask = nullptr;
    }

    {
        AutoLock l(mTerminatedMutex);
        isTerminated = true;
        mTerminatedCond->notify();
    }
}

//---------------ScheduleService---------------//
_ThreadScheduledPoolExecutor::_ThreadScheduledPoolExecutor() {
    mIsShutDown = false;
    mIsTerminated = false;
    mProtectMutex = createMutex("ScheduledThreadMutex");

    int cpuNum = st(System)::availableProcessors();
    mCachedExecutor = createThreadCachedPoolExecutor(cpuNum*4,60*1000);
    
    mTimeThread = createScheduledThreadPoolThread(mCachedExecutor);
    mTimeThread->start();
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
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    AutoLock l(mProtectMutex);
    
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;
    mTimeThread->stop();
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
    if(mIsShutDown) {
        return nullptr;
    }

    AutoLock l(mProtectMutex);

    if(mIsShutDown) {
        return nullptr;
    }

    return schedule(r,0);
}

Future _ThreadScheduledPoolExecutor::schedule(Runnable r,long delay) {
    
    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);

    Future future = createFuture(task);

    WaitingTask pooltask = createWaitingTask(task,delay);
    mTimeThread->addTask(pooltask);
    
    return future;
}

Future _ThreadScheduledPoolExecutor::scheduleAtFixedRate(Runnable r,
                                long initialDelay,
                                long period) {

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);

    WaitingTask pooltask = createWaitingTask(task,initialDelay,ScheduletTaskFixRate,period);
    mTimeThread->addTask(pooltask);

    return future;
}

Future _ThreadScheduledPoolExecutor::scheduleWithFixedDelay(Runnable r,
                                long initialDelay,
                                long delay) {

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);

    WaitingTask pooltask = createWaitingTask(task,initialDelay,ScheduletTaskFixedDelay,delay);
    mTimeThread->addTask(pooltask);  

    return future;   
}

//called from Future->cancel
void _ThreadScheduledPoolExecutor::onCancel(FutureTask task) {
    mTimeThread->stopTask(task);
}

_ThreadScheduledPoolExecutor::~_ThreadScheduledPoolExecutor() { 
    if(!mIsShutDown) {
        //cannot throw exception in destructor
        LOGE(TAG,"Scheduled Thread Pool destruct error");
    }
}

}
