#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "System.hpp"
#include "ScheduledThreadPoolExecutor.hpp"
#include "Error.hpp"
#include "AutoMutex.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {
//---------------ScheduledTaskWorker-------------------//
_ScheduledTaskWorker::_ScheduledTaskWorker(sp<_ScheduledThreadPoolTask> t) {
    mTask = t;
}

void _ScheduledTaskWorker::run() {
    long int startMillseconds = 0;

    if(mTask->mScheduleTaskType == ScheduletTaskFixRate) {
        startMillseconds = st(System)::currentTimeMillis();
    }

    if(mTask->task->getType() == FUTURE_TASK_SUBMIT) {
        mTask->task->onRunning();
    }

    Runnable runnable = mTask->task->getRunnable();
    if(runnable != nullptr) {
        runnable->run();    
    }

    if(mTask->task->getType() == FUTURE_TASK_SUBMIT) {
        mTask->task->onComplete();
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


//---------------TimeThread---------------//
_ScheduledThreadPoolThread::_ScheduledThreadPoolThread() {
    mDatas = createArrayList<ScheduledThreadPoolTask>();

    mDataLock = createMutex("ScheduledThreadPoolDataMutex");
    mDataCond = createCondition();

    mTimeLock = createMutex("ScheduledThreadPoolTimeMutex");
    mTimeCond = createCondition();

    mTerminatedMutex = createMutex("ScheduledThreadPoolTermMutex");
    mTerminatedCond = createCondition();

    int cpuNum = st(System)::availableProcessors();
    cachedExecutor = createThreadCachedPoolExecutor(cpuNum*2,60*1000);

    isStop = false;
    isTerminated = false;
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
    AutoMutex l(mDataLock);
    isStop = true;
    //clear all task
    //printf("_ScheduledThreadPoolThread stop 1 \n");
    int size = mDatas->size();
    for(int i = 0;i < size;i++) {
        //printf("stop,mCurrentTask1 count is %d \n",mCurrentTask->getStrongCount());
        ScheduledThreadPoolTask scheduleTask = mCurrentTask;//mDatas->remove(0);
        //printf("stop,scheduleTask2 count is %d \n",scheduleTask->getStrongCount());
        scheduleTask->task->cancel();
        //printf("stop,scheduleTask3 count is %d \n",scheduleTask->getStrongCount());
    }
    //printf("_ScheduledThreadPoolThread stop 2 \n");
    mDataCond->notify();

    cachedExecutor->shutdown();
    //printf("_ScheduledThreadPoolThread stop 3 \n");
    this->quit();
    //printf("_ScheduledThreadPoolThread stop 4 \n");
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
    
    if(mCurrentTask != nullptr) {
        Runnable runnable = mCurrentTask->task->getRunnable();
        if(runnable != nullptr) {
            runnable->onInterrupt();
        }
        
        mCurrentTask = nullptr;
    }

    AutoMutex l(mTerminatedMutex);
    isTerminated = true;
    mTerminatedCond->notify();
}

void _ScheduledThreadPoolThread::run() {
    while(!isStop) {
        //printf("scheduledthreadpool trace1 \n");
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
            //printf("scheduledthreadpool trace2 \n");
            mCurrentTask = mDatas->get(0);
            //printf("scheduledthreadpool trace2,mCurrentTask count is %d \n",mCurrentTask->getStrongCount());  
            break;
        }
        
        //get first time to wait;
        long currentTime = st(System)::currentTimeMillis();
        long interval = mCurrentTask->mNextTime - currentTime;
        if(interval > 0) {
            AutoMutex l(mTimeLock);
            //printf("scheduledthreadpool trace3,mCurrentTask p: %x \n",mCurrentTask->task->getRunnable().get_pointer());
            mTimeCond->wait(mTimeLock,interval);
            //printf("scheduledthreadpool trace4 \n");
            continue;
        } else {
            {
                //printf("scheduledthreadpool trace5 \n");
                AutoMutex l(mDataLock);
                mDatas->remove(mCurrentTask);
                //printf("scheduledthreadpool trace6 \n");
            }

            if(mCurrentTask->task->getStatus() == FUTURE_CANCEL) {
                continue;
            }

            Runnable r = mCurrentTask->task->getRunnable();
            if(r != nullptr) {
                //printf("scheduledthreadpool trace7 \n");
                ScheduledTaskWorker worker = createScheduledTaskWorker(mCurrentTask);
                //printf("scheduledthreadpool trace8 \n");
                cachedExecutor->execute(worker);
                //printf("scheduledthreadpool trace9 \n");
            }
        }
    }

end:
    //printf("scheduledthreadpool trace10 \n");
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    mDatas->clear();
    AutoMutex l(mTerminatedMutex);
    isTerminated = true;
    mTerminatedCond->notify();
}

//---------------ScheduleService---------------//
_ScheduledThreadPoolExecutor::_ScheduledThreadPoolExecutor() {
    mTimeThread = createScheduledThreadPoolThread();
    mTimeThread->start();
    mIsShutDown = false;
    mProtectMutex = createMutex("ScheduledThreadMutex");
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

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;

    mTimeThread->stop();

    return 0;
}

bool _ScheduledThreadPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ScheduledThreadPoolExecutor::isTerminated() {
    return mTimeThread->isTerminated;
}

int _ScheduledThreadPoolExecutor::awaitTermination(long timeout) {
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
    }
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
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
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

_ScheduledThreadPoolExecutor::~_ScheduledThreadPoolExecutor() {
    //printf("_ScheduledThreadPoolExecutor destroy \n");
    shutdown();
}

}
