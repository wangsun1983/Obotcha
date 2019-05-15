#include <stdio.h>
#include <stdlib.h>

//#include "ScheduleService.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "ScheduledThreadPoolExecutor.hpp"

namespace obotcha {
//---------------ScheduledTaskWorker-------------------//
_ScheduledTaskWorker::_ScheduledTaskWorker(sp<_ScheduledThreadPoolTask> t) {
    mTask = t;
}

void _ScheduledTaskWorker::run() {
    //printf("ScheduledTaskWorker trace1 \n");
    long int startMillseconds = 0;

    if(mTask->mScheduleTaskType == ScheduletTaskFixRate) {
        startMillseconds = st(System)::currentTimeMillis();
    }

    if(mTask->task->getType() == FUTURE_TASK_SUBMIT) {
        mTask->task->onRunning();
    }
    //printf("ScheduledTaskWorker trace2 \n");

    Runnable runnable = mTask->task->getRunnable();
    if(runnable != nullptr) {
        runnable->run();    
    }
    //printf("ScheduledTaskWorker trace3 \n");

    if(mTask->task->getType() == FUTURE_TASK_SUBMIT) {
        mTask->task->onComplete();
    }

    //we should check the whether the Task is a repeated task;
    switch(mTask->mScheduleTaskType) {
        case ScheduletTaskFixRate: {
            long int current = st(System)::currentTimeMillis();
            long int interval = current - startMillseconds;

            printf("interval is %ld,repeatDelay is %ld \n",interval,mTask->repeatDelay);

            if(interval >= mTask->repeatDelay) {
                mTask->mNextTime = current;
            } else {
                mTask->mNextTime = current + (mTask->repeatDelay - interval);
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

    mDataLock = createMutex();
    mDataCond = createCondition();
    mTimeLock = createMutex();
    mTimeCond = createCondition();
    mTerminatedMutex = createMutex();
    mTerminatedCond = createCondition();
    int cpuNum = st(System)::availableProcessors();

    cachedExecutor = createThreadCachedPoolExecutor(cpuNum*2,60*1000);

    //mExecutorService = createThreadPoolExecutor();

    isStop = false;
    isTerminated = false;
}

void _ScheduledThreadPoolThread::onUpdate() {
    //printf("onUpdate trace1 \n");
    mDataCond->notify();
    
    //printf("onUpdate trace2 \n");
    //AutoMutex l2(mTimeLock);
    mTimeCond->notify();
}

void _ScheduledThreadPoolThread::addTask(ScheduledThreadPoolTask v) {
    AutoMutex l(mDataLock);
    //printf("addTask trace1 \n");
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
//printf("addTask trace2,index is %d \n",index);
    mDatas->insert(index,v);
    //printf("mDatas size is %d \n",mDatas->size());
    onUpdate();
    //printf("addTask trace3 \n");
}

void _ScheduledThreadPoolThread::stop() {
    isStop = true;

    //clear all task
    int size = mDatas->size();
    for(int i = 0;i < size;i++) {
        ScheduledThreadPoolTask scheduleTask = mDatas->remove(0);
        scheduleTask->task->cancel();
    }
    //mDatas->clear();
}

void _ScheduledThreadPoolThread::forceStop() {
    AutoMutex l(mDataLock);
    isStop = true;
    //clear all task
    int size = mDatas->size();
    //printf("_ScheduledThreadPoolThread stop before size is %d \n",size);
    for(int i = 0;i < size;i++) {
        ScheduledThreadPoolTask scheduleTask = mDatas->remove(0);
        scheduleTask->task->cancel();
    }
    //mDatas->clear();
    //printf("_ScheduledThreadPoolThread stop after size is %d \n",mDatas->size());

    this->exit();

    //mDatas->clear();
}

void _ScheduledThreadPoolThread::waitStop(long timeout) {
    AutoMutex l(mTerminatedMutex);
    if(!isTerminated) {
        mTerminatedCond->wait(mTerminatedMutex,timeout);
    }
}

void _ScheduledThreadPoolThread::run() {
    while(!isStop) {
        //printf("_ScheduledThreadPoolThread trace1 \n");
        ScheduledThreadPoolTask v;
        while(1) {
            //printf("_ScheduledThreadPoolThread trace1_1 \n");
            AutoMutex l(mDataLock);
            //printf("_ScheduledThreadPoolThread trace1_2 \n");
            if(mDatas->size() == 0) {
                //printf("_ScheduledThreadPoolThread trace1_3 \n");
                mDataCond->wait(mDataLock);
                //printf("_ScheduledThreadPoolThread trace1_4 \n");
                continue;
            }
            //printf("_ScheduledThreadPoolThread trace1_5 \n");
            v = mDatas->get(0);
            break;
        }
        //printf("_ScheduledThreadPoolThread trace2 \n");
        

        //get first time to wait;
        //ScheduledThreadPoolTask v = mDatas->remove(0);
        long currentTime = st(System)::currentTimeMillis();
        long interval = v->mNextTime - currentTime;
        if(interval > 0) {
            //printf("_ScheduledThreadPoolThread trace3 \n");
            AutoMutex l(mTimeLock);
            mTimeCond->wait(mTimeLock,interval);
            //printf("_ScheduledThreadPoolThread trace4 \n");
            continue;
        } else {
            AutoMutex l(mDataLock);
            //printf("_ScheduledThreadPoolThread trace5 \n");
            mDatas->remove(v);

            Runnable r = v->task->getRunnable();
            if(r != nullptr) {
                printf("_ScheduledThreadPoolThread trace6 \n");
                ScheduledTaskWorker worker = createScheduledTaskWorker(v);

                //if(v->mScheduleTaskType != ScheduletTaskNormal) {
                //    worker->setTimeThread(mTimeThread);
                //}
                
                printf("_ScheduledThreadPoolThread trace7 \n");
                cachedExecutor->execute(worker);
            }
        }
    }

    //mExecutorService->execute(v->mRunnable);
    mDatas->clear();
    AutoMutex l(mTerminatedMutex);
    isTerminated = true;
    mTerminatedCond->notify();
}

//---------------ScheduleService---------------//
//_ScheduledThreadPoolExecutor::_ScheduledThreadPoolExecutor(int size) {
    //mPool = createConcurrentQueue<FutureTask>();
//    mTimeThread = createScheduledThreadPoolThread();
//    mTimeThread->start();
//    isShutDown = false;
//}

_ScheduledThreadPoolExecutor::_ScheduledThreadPoolExecutor() {    
    //mPool = createConcurrentQueue<FutureTask>();
    mTimeThread = createScheduledThreadPoolThread();
    mTimeThread->start();
    mIsShutDown = false;
}

void _ScheduledThreadPoolExecutor::execute(Runnable runnable) {
    //TODO
    //ScheduledThreadPoolTask task = createScheduledThreadPoolTask(runnable,millseconds);
    //mTimeThread->addTask(task);
    //return 0;
}

int _ScheduledThreadPoolExecutor::getThreadsNum() {
    //TODO
    return 0;
}

void _ScheduledThreadPoolExecutor::shutdown() {
    mIsShutDown = true;
    mTimeThread->stop();
}

void _ScheduledThreadPoolExecutor::shutdownNow() {
    mIsShutDown = true;
    mTimeThread->forceStop();
}

bool _ScheduledThreadPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ScheduledThreadPoolExecutor::isTerminated() {
    return mTimeThread->isTerminated;
}

bool _ScheduledThreadPoolExecutor::awaitTermination(long timeout) {
    mTimeThread->waitStop(timeout);
    return true;
}

Future _ScheduledThreadPoolExecutor::submit(Runnable r) {
    //FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    //Future future = createFuture(task);
    //return future;
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
    printf("_ScheduledThreadPoolExecutor destroy \n");
    shutdownNow();
}

}