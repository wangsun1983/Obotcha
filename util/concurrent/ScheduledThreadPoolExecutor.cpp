#include <stdio.h>
#include <stdlib.h>

//#include "ScheduleService.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "ScheduledThreadPoolExecutor.hpp"

namespace obotcha {
//---------------ScheduledTaskWorker-------------------//
_ScheduledTaskWorker::_ScheduledTaskWorker(FutureTask t) {
    mTask = t;
}

void _ScheduledTaskWorker::run() {
    //printf("ScheduledTaskWorker trace1 \n");
    if(mTask->getType() == FUTURE_TASK_SUBMIT) {
        mTask->onRunning();
    }
    //printf("ScheduledTaskWorker trace2 \n");

    Runnable runnable = mTask->getRunnable();
    if(runnable != nullptr) {
        runnable->run();    
    }
    //printf("ScheduledTaskWorker trace3 \n");

    if(mTask->getType() == FUTURE_TASK_SUBMIT) {
        mTask->onComplete();
    }
}

//---------------ScheduledThreadPoolTask---------------//
_ScheduledThreadPoolTask::_ScheduledThreadPoolTask(FutureTask t,long int interval) {
    task = t;
    millseconds = st(System)::currentTimeMillis() + interval;
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
        if(m->millseconds > v->millseconds) {
            end = index - 1;
        } else if(m->millseconds < v->millseconds) {
            start = index + 1;
        } else if(m->millseconds == v->millseconds) {
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
}

void _ScheduledThreadPoolThread::forceStop() {
    isStop = true;
    this->exit();
    mDatas->clear();
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
        long interval = v->millseconds - currentTime;
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
                //we should use dynamic thread pool
                //Thread t = createThread(r);
                //t->start();
                //printf("_ScheduledThreadPoolThread trace6 \n");
                ScheduledTaskWorker worker = createScheduledTaskWorker(v->task);
                Thread t = createThread(worker);
                t->start();
                //printf("_ScheduledThreadPoolThread trace7 \n");
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

Future _ScheduledThreadPoolExecutor::scheduleAtFixedRate(Runnable command,
                                long initialDelay,
                                long period) {
    //TODO
}

Future _ScheduledThreadPoolExecutor::scheduleWithFixedDelay(Runnable command,
                                long initialDelay,
                                long delay) {
    //TODO        
}

}