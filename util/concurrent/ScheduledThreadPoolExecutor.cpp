#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "System.hpp"
#include "ScheduledThreadPoolExecutor.hpp"
#include "Error.hpp"
#include "AutoMutex.hpp"
#include "MethodNotSupportException.hpp"
#include "ExecutorDestructorException.hpp"

namespace obotcha {
//---------------ScheduledTaskWorker-------------------//
_ScheduledTaskWorker::_ScheduledTaskWorker(sp<_ScheduledThreadPoolTask> t,ScheduledThreadPoolThread thread) {
    mTask = t;
    mTimeThread = thread;
}

_ScheduledTaskWorker::~_ScheduledTaskWorker() {
    printf("_ScheduledTaskWorker release \n");
    mTimeThread.remove_pointer();
}

void _ScheduledTaskWorker::onInterrupt() {
    printf("_ScheduledTaskWorker onInterrupt start this is %llx",this);

    Runnable r = nullptr;
    if(mTask != nullptr) {
        r = mTask->task->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
    }

    if(mTimeThread != nullptr && r != nullptr) {
        printf("_ScheduledTaskWorker onInterrupt trace r is %llx",r.get_pointer());
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
            mTask->mNextTime = st(System)::currentTimeMillis();
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
                printf("_ScheduledTaskWorker run complete \n");
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
    printf("_ScheduledThreadPoolTask release \n");
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
    printf("schedulethread start release \n");
    {
        AutoMutex ll(mFuturesMutex);
        mFutures->clear();
    }
    printf("schedulethread release \n");
    
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
        //printf("mDatas before size is %d \n",mDatas->size());
        mDatas->clear();
        //printf("mDatas after size is %d \n",mDatas->size());
    }

    mFutures->clear();

    this->quit();
    
    printf("_ScheduledThreadPoolThread stop1 start,count is %d \n",this->getStrongCount());
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
    
    printf("ScheduledThreadPoolThread onInterrupt start \n");
    //CachedExector will clear mCurrentTask's runnable;
    {
        AutoMutex l(mTerminatedMutex);
        isTerminated = true;
        mTerminatedCond->notify();
    }
    
    printf("ScheduledThreadPoolThread onInterrupt trace1 \n");
    //clear all task
    if(mCurrentTask != nullptr) {
        if(mCurrentTask->task != nullptr) {
            mCurrentTask->task->cancel();
        }
    }

    printf("ScheduledThreadPoolThread onInterrupt trace2 \n");
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

    printf("ScheduledThreadPoolThread onInterrupt trace3 \n");
    mCurrentTask = nullptr;
}

void _ScheduledThreadPoolThread::stopTask(FutureTask task) {
    {
        printf("_ScheduledThreadPoolThread stop task trace \n");
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
            printf("before remove size is %d \n",mDatas->size());
            mDatas->remove(t);
            t->mTimeThread = nullptr;
            printf("after remove size is %d \n",mDatas->size());
            return;
        }
    }
    
    {
        printf("_ScheduledThreadPoolThread stoptask trace2  \n");
        Runnable r = task->getRunnable();
        printf("_ScheduledThreadPoolThread stop task trace2_2,runnable is %lld \n",r.get_pointer());
        AutoMutex ll(mFuturesMutex);
        Future f = mFutures->get(r);
        //printf("_ScheduledThreadPoolThread stop task trace2_3 \n");
        if(f != nullptr) {
        //    printf("_ScheduledThreadPoolThread stop task trace3 \n");
            f->cancel();
        } else if(task == mCurrentTask) {
            mCurrentTask->task->cancel();
        }
        printf("_ScheduledThreadPoolThread stop task trace4 \n");
        mFutures->remove(r);
    }
}

void _ScheduledThreadPoolThread::onTaskFinished(Runnable r) {
    Future f = nullptr;
    printf("onTaskFinished r is %llx\n",r.get_pointer());
    {
        AutoMutex ll(mFuturesMutex);
        //f = mFutures->get(r);
        //if(f == nullptr) {
        //    return;
        //}
        printf("mFutures before size is %d \n",mFutures->size());
        mFutures->remove(r);
        printf("mFutures after size is %d \n",mFutures->size());
    }
}

void _ScheduledThreadPoolThread::run() {
    printf("scheculet thread pool thread start \n");
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
        printf("scheculet thread pool thread trace1 \n");
        
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
            printf("schedule thread do run \n");
            Runnable r = mCurrentTask->task->getRunnable();
            if(r != nullptr) {
                ScheduledThreadPoolThread t;
                t.set_pointer(this);

                ScheduledTaskWorker worker = createScheduledTaskWorker(mCurrentTask,t);
                printf("submit task current time is %ld \n",st(System)::currentTimeMillis());
                Future future = cachedExecutor->submit(worker);
                {
                    printf("add future to mFutures,runnable is %lld \n",r.get_pointer());
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
    printf("_ScheduledThreadPoolExecutor create \n");
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
    throw createMethodNotSupportException(createString("getThreadsNum not support"));
    return 0;
}

int _ScheduledThreadPoolExecutor::shutdown() {
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }
    printf("shutdown trace0 \n");
    AutoMutex l(mProtectMutex);
    printf("shutdown trace1 \n");

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }
    printf("shutdown trace2 \n");
    mIsShutDown = true;
    mTimeThread->stop();
    printf("shutdown trace3 \n");
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
    printf("submit start \n");
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
    printf("schedule start \n");

    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);

    Future future = createFuture(task);

    printf("future's runnable is %lld \n",task->getRunnable().get_pointer());

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
    printf("_ScheduledThreadPoolExecutor,onCancel1,task runnable is %lld \n",task->getRunnable().get_pointer());
    mTimeThread->stopTask(task);
    printf("_ScheduledThreadPoolExecutor,onCancel2 \n");
}

_ScheduledThreadPoolExecutor::~_ScheduledThreadPoolExecutor() {
    printf("~_ScheduledThreadPoolExecutor \n");
    //shutdown();
    if(!mIsShutDown) {
        throw createExecutorDestructorException("Scheduled Thread Pool destruct error");
    }
}

}
