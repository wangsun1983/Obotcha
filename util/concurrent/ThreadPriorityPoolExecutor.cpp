#include <stdio.h>
#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "Executor.hpp"
#include "Callable.hpp"
#include "ConcurrentQueue.hpp"
#include "ExecutorService.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "System.hpp"
#include "StackTrace.hpp"
#include "ExecutorDestructorException.hpp"
#include "Log.hpp"
#include "TimeWatcher.hpp"

namespace obotcha {

#define TAG "ThreadPriorityPoolExecutor"

//============= PriorityPoolThread =================
_PriorityPoolThread::_PriorityPoolThread(PriorityTaskManager mgr,ThreadPriorityPoolExecutor exe) {
    
    mExecutor = exe;

    mTaskMgr = mgr;

    mExecutorMutex = createMutex("ThreadPriorityPoolExecutorMutex");

    mStop = false;
}

void _PriorityPoolThread::run() {
    while(!mStop) {
        mCurrentTask = mTaskMgr->getTask();
        
        if(mCurrentTask == nullptr) {
            printf("mCurrentTask is nullptr!!!! \n");
            break;
        }

        if(mCurrentTask->task->getStatus() == st(Future)::Cancel) {
            continue;
        }

        {
            if(mCurrentTask->task->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->task->onRunning();
            }
        }

        Runnable runnable = mCurrentTask->task->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }

        {
            if(mCurrentTask->task->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->task->onComplete();
            }
        }
    }

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    
    {
        AutoLock ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            PriorityPoolThread thread;
            thread.set_pointer(this);
            mExecutor->onCompleteNotify(thread);
            mExecutor.remove_pointer();
        }
    }
}

void _PriorityPoolThread::onInterrupt() {
    //printf("_PriorityPoolThread onInterrupt \n");
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->task->getRunnable();
        if(r != nullptr) {
            //printf("_PriorityPoolThread onInterrupt2 \n");
            r->onInterrupt();
        }
        mCurrentTask = nullptr;
        r = nullptr;
    }

    {
        AutoLock ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            PriorityPoolThread thread;
            thread.set_pointer(this);
            mExecutor->onCompleteNotify(thread);
            mExecutor.remove_pointer();
        }
    }
}

bool _PriorityPoolThread::foceStopTask(FutureTask t) {
    if(mCurrentTask != nullptr && mCurrentTask->task == t) {
        stop();
        return true;
    }

    return false;
}

_PriorityPoolThread::~_PriorityPoolThread() {
}

void _PriorityPoolThread::stop() {
    mStop = true;
    this->quit();
}

//============= PriorityTaskManager ================
_PriorityTaskManager::_PriorityTaskManager() {
    mHighPriorityTasks = createConcurrentQueue<PriorityTask>();
    mMediumPriorityTasks = createConcurrentQueue<PriorityTask>();
    mLowPriorityTasks = createConcurrentQueue<PriorityTask>();
    mTaskMutex = createMutex();
    mTaskCondition = createCondition();
}

void _PriorityTaskManager::addTask(PriorityTask task) {
    switch(task->priority) {
        case st(ThreadPriorityPoolExecutor)::PriorityHigh:
            mHighPriorityTasks->enQueueLast(task);
        break;

        case st(ThreadPriorityPoolExecutor)::PriorityMedium:
            mMediumPriorityTasks->enQueueLast(task);
            //printf("enqueue,mMediumPriorityTasks size is %d \n",mMediumPriorityTasks->size());
        break;

        case st(ThreadPriorityPoolExecutor)::PriorityLow:
            mLowPriorityTasks->enQueueLast(task);
        break;
    }

    {
        AutoLock l(mTaskMutex);
        mTaskCondition->notify();
    }
}

int _PriorityTaskManager::cancel(FutureTask task) {
    AutoLock l(mTaskMutex);
    
    int size = mHighPriorityTasks->size();
    for(int i = 0;i<size;i++) {
        if(mHighPriorityTasks->get(i)->task == task) {
            return 0;
        }
    }

    size = mMediumPriorityTasks->size();
    for(int i = 0;i<size;i++) {
        if(mMediumPriorityTasks->get(i)->task == task) {
            return 0;
        }
    }

    size = mLowPriorityTasks->size();
    for(int i = 0;i<size;i++) {
        if(mLowPriorityTasks->get(i)->task == task) {
            return 0;
        }
    }

    return -1;
}

PriorityTask _PriorityTaskManager::getTask() {
    while(1) {
        AutoLock l(mTaskMutex);
        PriorityTask t = mHighPriorityTasks->deQueueFirst();
        if(t != nullptr) {
            return t;
        }

        t = mMediumPriorityTasks->deQueueFirst();
        if(t != nullptr) {
            return t;
        }

        t = mLowPriorityTasks->deQueueFirst();
        if(t != nullptr) {
            return t;
        }
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
        mTaskCondition->wait(mTaskMutex);
    }
}

void _PriorityTaskManager::cancelAll() {
    AutoLock l(mTaskMutex);
    //printf("cancelAll,mHighPriorityTasks size is %d,mMediumPriorityTasks size is %d,mLowPriorityTasks size is %d \n",
    //mHighPriorityTasks->size(),
    //mMediumPriorityTasks->size(),
    //mLowPriorityTasks->size());

    int size = mHighPriorityTasks->size();
    for(int i = 0;i<size;i++) {
        PriorityTask task = mHighPriorityTasks->get(i);
        task->task->cancelWithoutCallback();
    }

    size = mMediumPriorityTasks->size();
    for(int i = 0;i<size;i++) {
        PriorityTask task = mMediumPriorityTasks->get(i);
        task->task->cancelWithoutCallback();
    }

    size = mLowPriorityTasks->size();
    for(int i = 0;i<size;i++) {
        PriorityTask task = mLowPriorityTasks->get(i);
        task->task->cancelWithoutCallback();
    }

    mHighPriorityTasks->clear();
    mMediumPriorityTasks->clear();
    mLowPriorityTasks->clear();
}


//============= ThreadPriorityPoolExecutor ================
_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor():_ThreadPriorityPoolExecutor{1} {
    //do nothing
}

_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor(int threadnum) {
    mProtectMutex = createMutex("PriorityMutex");
    mDataLock = createMutex("PriorityData");
    mDataCond = createCondition();
    mWaitMutex = createMutex("PriorityWaitMutex");
    mWaitCondition = createCondition();

    mThreadMutex = createMutex("PriorityThread Mutex");
    mThreads = createArrayList<PriorityPoolThread>();

    mPriorityTaskMgr = createPriorityTaskManager();

    ThreadPriorityPoolExecutor exe;
    exe.set_pointer(this);

    mThreadNum = threadnum;
    for(int i = 0;i < threadnum;i++) {
        PriorityPoolThread thread = createPriorityPoolThread(mPriorityTaskMgr,exe);
        thread->start();
        mThreads->add(thread);
    }
    
    isShutDown = false;
    isTermination = false;
}

int _ThreadPriorityPoolExecutor::execute(Runnable r) {
    return execute(PriorityMedium,r);
}

int _ThreadPriorityPoolExecutor::execute(int level,Runnable r) {
    if(submit(level,r) == nullptr) {
        return -InvalidStatus;
    }

    return 0;
}

int _ThreadPriorityPoolExecutor::shutdown() {
    if(isShutDown) {
        return 0;
    }

    mPriorityTaskMgr->cancelAll();
    
    {
        AutoLock l(mProtectMutex);

        if(isShutDown) {
            return 0;
        }

        isShutDown = true;

        AutoLock ll(mThreadMutex);
        ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolThread thread = iterator->getValue();
            thread->stop();
            iterator->next();
        }
    }
}

bool _ThreadPriorityPoolExecutor::isTerminated() {
    return isTermination;
}

void _ThreadPriorityPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadPriorityPoolExecutor::awaitTermination(long millseconds) {
    if(!isShutDown) {
        return -InvalidStatus;
    }

    if(isTermination) {
        return 0;
    }
    
    AutoLock ll(mWaitMutex);
    if(isTermination) {
        return 0;
    }

    return mWaitCondition->wait(mWaitMutex,millseconds);
}

Future _ThreadPriorityPoolExecutor::submit(Runnable task) {
    return submit(PriorityMedium,task);
}

Future _ThreadPriorityPoolExecutor::submit(int level,Runnable task) {
    if(isShutDown || isTermination) {
        return nullptr;
    }

    AutoLock l(mProtectMutex);
    
    if(isShutDown || isTermination) {
        return nullptr;
    }

    FutureTaskStatusListener listener;
    listener.set_pointer(this);

    FutureTask futureTask = createFutureTask(FUTURE_TASK_SUBMIT,task,listener);
    mPriorityTaskMgr->addTask(createPriorityTask(level,futureTask));
    return createFuture(futureTask);
}

int _ThreadPriorityPoolExecutor::getThreadsNum() {
    AutoLock ll(mProtectMutex);
    return mThreads->size();
}

void _ThreadPriorityPoolExecutor::onCompleteNotify(PriorityPoolThread t){
    AutoLock ll(mThreadMutex);
    ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
    while(iterator->hasValue()) {
        PriorityPoolThread thread = iterator->getValue();
        if(thread == t) {
            iterator->remove();
            break;
        }
        iterator->next();
    }

    if(mThreads->size() == 0) {
        mThreads->clear();
        AutoLock ll(mWaitMutex);
        isTermination = true;
        mWaitCondition->notifyAll();
    }
}

void _ThreadPriorityPoolExecutor::onCancel(FutureTask task) {
    if(isShutDown ||isTermination) {
        return;
    }

    AutoLock l(mProtectMutex);

    if(isShutDown ||isTermination) {
        return;
    }

    //do not need to remove
    //if(mPriorityTaskMgr->cancel(task) == 0) {
    //    return;
    //}
    
    {
        bool isNeedCreate = false;
        AutoLock ll(mThreadMutex);
        ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolThread thread = iterator->getValue();
            
            if(thread->foceStopTask(task)) {
                isNeedCreate = true;
                iterator->remove();
                break;
            }

            iterator->next();
        }
        
        if(isNeedCreate) {
            AutoLock ll(mProtectMutex);
            ThreadPriorityPoolExecutor exe;
            exe.set_pointer(this);

            PriorityPoolThread thread = createPriorityPoolThread(mPriorityTaskMgr,exe);
            thread->start();
            mThreads->add(thread);
        }
    }

}

_ThreadPriorityPoolExecutor::~_ThreadPriorityPoolExecutor() {
    
    if(!isShutDown) {
        LOGE(TAG,"Priority Thread Pool destruct error");
    }
}

//============== PriorityTask ================
_PriorityTask::_PriorityTask(int level ,FutureTask f) {
    priority = level;
    task = f;
}

}
