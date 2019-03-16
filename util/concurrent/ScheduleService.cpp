#include <stdio.h>
#include <stdlib.h>

#include "ScheduleService.hpp"
#include "Thread.hpp"
#include "System.hpp"

namespace obotcha {

//---------------TimeTask---------------//
_TimeTask::_TimeTask(Runnable runnable,long int interval) {
    mRunnable = runnable;
    millseconds = st(System)::currentTimeMillis() + interval;
}


//---------------TimeThread---------------//
_TimeThread::_TimeThread() {
    mDatas = createArrayList<TimeTask>();
    mDataLock = createMutex();

    mCondLock = createMutex();
    mCond = createCondition();

    mExecutorService = createExecutorService();
}

void _TimeThread::onUpdate() {
    AutoMutex l(mCondLock);
    mCond->notify();
}

void _TimeThread::addTask(TimeTask v) {
    AutoMutex l(mDataLock);

    int start = 0;
    int end = mDatas->size() - 1;
    int index = 0;
    while(start <= end) {
        index = (start+end)/2;
        TimeTask m = mDatas->get(index);
        if(m->millseconds > v->millseconds) {
            end = index - 1;
        } else if(m->millseconds < v->millseconds) {
            start = index + 1;
        } else if(m->millseconds == v->millseconds) {
            break;
        }
    }

    mDatas->insert(index,v);
    onUpdate();
}

void _TimeThread::run() {
    while(true) {
        if(mDatas->size() == 0) {
            AutoMutex l(mCondLock);
            mCond->wait(mCondLock);
        } 

        //get first time to wait;
        TimeTask v = mDatas->remove(0);

        {
            AutoMutex l(mCondLock);
            long currentTime = st(System)::currentTimeMillis();
            long interval = v->millseconds - currentTime;
            if(interval > 0) {
                mCond->wait(mCondLock,interval);
            }
        }

        mExecutorService->execute(v->mRunnable);
    }
}

//---------------ScheduleService---------------//
_ScheduleService::_ScheduleService(int size) {
    mPool = ConcurrentQueue<Runnable>();
    mTimeThread = createTimeThread();
    mTimeThread->start();
}

_ScheduleService::_ScheduleService() {    
    mPool = ConcurrentQueue<Runnable>();
    mTimeThread = createTimeThread();
    mTimeThread->start();
}

int _ScheduleService::execute(Runnable runnable,long millseconds) {
    TimeTask task = createTimeTask(runnable,millseconds);
    mTimeThread->addTask(task);
    return 0;
}

void _ScheduleService::shutdown() {
    //TODO
}

void _ScheduleService::awaitTermination() {
    //TODO
}

void _ScheduleService::awaitTermination(long millseconds) {

}

_ScheduleService::~_ScheduleService() {

}

}