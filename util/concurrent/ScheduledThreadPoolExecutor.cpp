#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "System.hpp"
#include "ScheduledThreadPoolExecutor.hpp"
#include "Error.hpp"
#include "AutoMutex.hpp"
#include "MethodNotSupportException.hpp"
#include "ExecutorDestructorException.hpp"
#include "Log.hpp"

namespace obotcha {

#define TAG "ScheduledThreadPool"

//---------------ScheduledTaskWorker-------------------//
_ScheduledTaskWorker::_ScheduledTaskWorker(sp<_ScheduledThreadPoolTask> t,ScheduledThreadPoolThread thread) {
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
            
            mTask->mTimeThread->addTask(mTask);
        }
        break;

        case ScheduletTaskFixedDelay: {
            long int current = st(System)::currentTimeMillis();
            mTask->mNextTime = current + mTask->repeatDelay;
            mTask->mTimeThread->addTask(mTask);
        }
        break;

        case ScheduletTaskNormal:{
            if(mTimeThread != nullptr) {
                mTimeThread->onTaskFinished(runnable);
                mTimeThread.remove_pointer();
            }
        }
        break;
    }
}

//---------------ScheduledThreadPoolTask---------------//
_ScheduledThreadPoolTask::_ScheduledThreadPoolTask(FutureTask t,long int interval) {
    task = t;
    mNextTime = st(System)::currentTimeMillis() + interval;
    mScheduleTaskType = ScheduletTaskNormal;
}

_ScheduledThreadPoolTask::_ScheduledThreadPoolTask(FutureTask t,
                                                   long int interval,
                                                   int type,
                                                   long int delay,
                                                   sp<_ScheduledThreadPoolThread> timethread) {
    task = t;
    mNextTime = st(System)::currentTimeMillis() + interval;
    mScheduleTaskType = type;
    mTimeThread = timethread;
    repeatDelay = delay;
}

_ScheduledThreadPoolTask::~_ScheduledThreadPoolTask() {
    task = nullptr;
    mTimeThread.remove_pointer();
}


//---------------TimeThread---------------//
_ScheduledThreadPoolThread::_ScheduledThreadPoolThread(ThreadCachedPoolExecutor m) {
    mDatas = createArrayList<ScheduledThreadPoolTask>();

    mDataLock = createMutex("ScheduledThreadPoolDataMutex");
    mDataCond = createCondition();

    mTimeLock = createMutex("ScheduledThreadPoolTimeMutex");
    mTimeCond = createCondition();

    mTerminatedMutex = createMutex("ScheduledThreadPoolTermMutex");
    mTerminatedCond = createCondition();

    mFuturesMutex = createMutex("ScheduledThreadPoolFutureMutex");
    mFutures = createHashMap<Runnable,Future>();
    
    cachedExecutor = m;

    isStop = false;
    isTerminated = false;
}

_ScheduledThreadPoolThread::~_ScheduledThreadPoolThread() {
    {
        AutoMutex ll(mFuturesMutex);
        mFutures->clear();
    }
    
}

void _ScheduledThreadPoolThread::onUpdate() {
    mDataCond->notify();
    mTimeCond->notify();
}

void _ScheduledThreadPoolThread::addTask(ScheduledThreadPoolTask v) {
    
    AutoMutex l(mDataLock);
    int start = 0;
    int end = mDatas->size() - 1;
    int index = 0;
    while(start <= end) {
        index = (start+end)/2;
        ScheduledThreadPoolTask m = mDatas->get(index);
        if(m->mNextTime > v->mNextTime) {
            end = index - 1;
        } else if(m->mNextTime < v->mNextTime) {
            start = index + 1;
        } else if(m->mNextTime == v->mNextTime) {
            break;
        }
    }

    mDatas->insert(index,v);

    onUpdate();
}

void _ScheduledThreadPoolThread::stop() {
    {
        AutoMutex ll(mDataLock);
        mDatas->clear();
    }

    mFutures->clear();

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

    AutoMutex l(mTerminatedMutex);

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
        AutoMutex l(mTerminatedMutex);
        isTerminated = true;
        mTerminatedCond->notify();
    }
    
    //clear all task
    if(mCurrentTask != nullptr) {
        if(mCurrentTask->task != nullptr) {
            mCurrentTask->task->cancel();
        }
    }

    {
        AutoMutex ll(mDataLock);
        ListIterator<ScheduledThreadPoolTask> iterator = mDatas->getIterator();
        //int i = 0;
        while(iterator->hasValue()) {
            ScheduledThreadPoolTask t = iterator->getValue();
            if(t != mCurrentTask) {
                t->task->cancel();
            }
            iterator->next();
        }

        mDatas->clear();
    }

    mCurrentTask = nullptr;
}

void _ScheduledThreadPoolThread::stopTask(FutureTask task) {
    {
        AutoMutex l(mDataLock);
        //if(mDatas->remove(task) > 0) {
        //    return;
        //}
        ListIterator<ScheduledThreadPoolTask> iterator = mDatas->getIterator();
        ScheduledThreadPoolTask t = nullptr;
        while(iterator->hasValue()) {
            t = iterator->getValue();
            if(t->task == task) {
                break;
            }
            iterator->next();
        }

        if(t != nullptr) {
            mDatas->remove(t);
            t->mTimeThread = nullptr;
            return;
        }
    }
    
    {
    
        Runnable r = task->getRunnable();
        AutoMutex ll(mFuturesMutex);
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
    Future f = nullptr;
    {
        AutoMutex ll(mFuturesMutex);
        //f = mFutures->get(r);
        //if(f == nullptr) {
        //    return;
        //}
        mFutures->remove(r);
    }
}

void _ScheduledThreadPoolThread::run() {
    while(!isStop) {
        st(Thread)::interruptCheck();
        mCurrentTask = nullptr;
        while(1) {
            AutoMutex l(mDataLock);
            if(isStop) {
                goto end;
            }

            if(mDatas->size() == 0) {
                mDataCond->wait(mDataLock);
                continue;
            }
            mCurrentTask = mDatas->get(0);
            break;
        }
         
        //get first time to wait;
        long currentTime = st(System)::currentTimeMillis();
        long interval = mCurrentTask->mNextTime - currentTime;
        if(interval > 0) {
            AutoMutex l(mTimeLock);
            mTimeCond->wait(mTimeLock,interval);
            continue;
        } else {
            {
                AutoMutex l(mDataLock);
                if(mDatas->remove(mCurrentTask) < 0) {
                    continue;
                }
            }

            if(mCurrentTask->task->getStatus() == FUTURE_CANCEL) {
                continue;
            }
            Runnable r = mCurrentTask->task->getRunnable();
            if(r != nullptr) {
                ScheduledThreadPoolThread t;
                t.set_pointer(this);

                ScheduledTaskWorker worker = createScheduledTaskWorker(mCurrentTask,t);
                Future future = cachedExecutor->submit(worker);
                {
                    AutoMutex ll(mFuturesMutex);
                    mFutures->put(r,future);
                }
            }
        }
    }

end:
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    mCurrentTask = nullptr;

    mDatas->clear();
    AutoMutex l(mTerminatedMutex);
    isTerminated = true;
    mTerminatedCond->notify();
}

//---------------ScheduleService---------------//
_ScheduledThreadPoolExecutor::_ScheduledThreadPoolExecutor() {
    mIsShutDown = false;
    mIsTerminated = false;
    mProtectMutex = createMutex("ScheduledThreadMutex");

    int cpuNum = st(System)::availableProcessors();
    mCachedExecutor = createThreadCachedPoolExecutor(cpuNum*2,60*1000);
    
    mTimeThread = createScheduledThreadPoolThread(mCachedExecutor);
    mTimeThread->start();
}

int _ScheduledThreadPoolExecutor::execute(Runnable runnable) {
    
    if(submit(runnable) == nullptr) {
        return -InvalidStatus;
    }

    return 0;
}

int _ScheduledThreadPoolExecutor::getThreadsNum() {
    throw MethodNotSupportException(createString("getThreadsNum not support"));
    return 0;
}

int _ScheduledThreadPoolExecutor::shutdown() {
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }
    AutoMutex l(mProtectMutex);
    
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }
    mIsShutDown = true;
    mTimeThread->stop();
    //startWaitTerminate();
    return 0;
}

bool _ScheduledThreadPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ScheduledThreadPoolExecutor::isTerminated() {
    //return mTimeThread->isTerminated;
    return mCachedExecutor->isTerminated();
}

int _ScheduledThreadPoolExecutor::awaitTermination(long timeout) {
    /*
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    if(mIsTerminated) {
        return 0;
    }

    mTimeThread->waitForTerminate(timeout);

    if(isTerminated()) {
        return 0;
    } else {
        return -WaitTimeout;
    }*/
    return mCachedExecutor->awaitTermination(timeout);
}

Future _ScheduledThreadPoolExecutor::submit(Runnable r) {
    if(mIsShutDown) {
        return nullptr;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown) {
        return nullptr;
    }

    return schedule(r,0);
}

Future _ScheduledThreadPoolExecutor::schedule(Runnable r,long delay) {
    
    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);

    Future future = createFuture(task);

    ScheduledThreadPoolTask pooltask = createScheduledThreadPoolTask(task,delay);
    mTimeThread->addTask(pooltask);
    
    return future;
}

Future _ScheduledThreadPoolExecutor::scheduleAtFixedRate(Runnable r,
                                long initialDelay,
                                long period) {

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);

    ScheduledThreadPoolTask pooltask = createScheduledThreadPoolTask(task,
                                                                     initialDelay,
                                                                     ScheduletTaskFixRate,
                                                                     period,
                                                                     mTimeThread);
    mTimeThread->addTask(pooltask);

    return future;
}

Future _ScheduledThreadPoolExecutor::scheduleWithFixedDelay(Runnable r,
                                long initialDelay,
                                long delay) {

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);

    ScheduledThreadPoolTask pooltask = createScheduledThreadPoolTask(task,
                                                                     initialDelay,
                                                                     ScheduletTaskFixedDelay,
                                                                     delay,
                                                                     mTimeThread);
    mTimeThread->addTask(pooltask);  

    return future;   
}

void _ScheduledThreadPoolExecutor::onCancel(FutureTask task) {
    mTimeThread->stopTask(task);
}

_ScheduledThreadPoolExecutor::~_ScheduledThreadPoolExecutor() {
    //shutdown();
    if(!mIsShutDown) {
        //cannot throw exception in destructor
        //throw ExecutorDestructorException("Scheduled Thread Pool destruct error");
        LOGE(TAG,"Scheduled Thread Pool destruct error");
    }
}

}
