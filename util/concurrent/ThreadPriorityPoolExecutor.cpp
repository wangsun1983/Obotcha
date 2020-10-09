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
#include "Executors.hpp"

namespace obotcha {

#define TAG "ThreadPriorityPoolExecutor"

//============= PriorityPoolThread =================
_PriorityPoolThread::_PriorityPoolThread(LinkedList<PriorityTask> high,
                                         LinkedList<PriorityTask> mid,
                                         LinkedList<PriorityTask> low,
                                         Mutex listmutex,
                                         Condition listcond) {
    
    highTasks = high;
    midTasks = mid;
    lowTasks = low;
    mMutex = listmutex;
    mCond = listcond;
    mCurrentTaskMutex = createMutex("PriorityMutex");
    mStop = false;
}

PriorityTask _PriorityPoolThread::getTask() {
    while(1) {
        AutoLock l(mMutex);
        PriorityTask task = nullptr;
        if(highTasks->size() > 0) {
            task = highTasks->deQueueFirst();
            if(task->task == nullptr) {
                highTasks->enQueueLast(task);
                return nullptr;
            }
        }

        if(midTasks->size() > 0) {
            task = midTasks->deQueueFirst();
            if(task->task == nullptr) {
                midTasks->enQueueLast(task);
                return nullptr;
            }
        }

        if(lowTasks->size() > 0) {
            task = lowTasks->deQueueFirst();
            if(task->task == nullptr) {
                lowTasks->enQueueLast(task);
                return nullptr;
            }
        }

        mCond->wait(mMutex);
    }
}

void _PriorityPoolThread::run() {
    while(!mStop) {
        mCurrentTask = getTask();
        
        if(mCurrentTask == nullptr) {
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
        
        {    
            AutoLock l(mCurrentTaskMutex);
            mCurrentTask = nullptr;
        }
    }

}

bool _PriorityPoolThread::shutdownTask(FutureTask task) {
    AutoLock l(mCurrentTaskMutex);
    if(mCurrentTask != nullptr && mCurrentTask->task == task) {
        stop();
        return true;
    }

    return false;
}

void _PriorityPoolThread::onInterrupt() {
    printf("_PriorityPoolThread onInterrupt");
    if(mCurrentTask!= nullptr &&mCurrentTask->task->getStatus() == st(Future)::Running) {
        Runnable r = mCurrentTask->task->getRunnable();
        printf("_PriorityPoolThread onInterrupt trace1");
        if(r != nullptr) {
            r->onInterrupt();
        }
    }
    printf("_PriorityPoolThread onInterrupt trace2");
    mCurrentTask = nullptr;
}

_PriorityPoolThread::~_PriorityPoolThread() {
}

void _PriorityPoolThread::stop() {
    mStop = true;
    this->quit();
}


//============= ThreadPriorityPoolExecutor ================
_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor():_ThreadPriorityPoolExecutor{1} {
    //do nothing
}

_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor(int threadnum) {
    mStatusMutex = createMutex("PriorityStatusMutex");
    mTaskMutex = createMutex("PriorityData");
    mTaskCond = createCondition();

    mThreadMutex = createMutex("PriorityThread Mutex");
    mThreads = createArrayList<PriorityPoolThread>();

    mHighPriorityTasks = createLinkedList<PriorityTask>();
    mMidPriorityTasks = createLinkedList<PriorityTask>();
    mLowPriorityTasks = createLinkedList<PriorityTask>();

    mThreadNum = threadnum;
    for(int i = 0;i < threadnum;i++) {
        PriorityPoolThread thread = createPriorityPoolThread(mHighPriorityTasks,
                                                             mMidPriorityTasks,
                                                             mLowPriorityTasks,
                                                             mTaskMutex,
                                                             mTaskCond);
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
    {
        AutoLock l(mStatusMutex);

        if(isShutDown) {
            return 0;
        }

        isShutDown = true;
    }

    {
        AutoLock ll(mThreadMutex);
        ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolThread thread = iterator->getValue();
            thread->stop();
            thread->detach();
            iterator->next();
        }
    }

    {
        AutoLock l(mTaskMutex);
        while(!mHighPriorityTasks->isEmpty()) {
            mHighPriorityTasks->deQueueLast();
        }

        while(!mMidPriorityTasks->isEmpty()) {
            mMidPriorityTasks->deQueueLast();
        }

        while(!mLowPriorityTasks->isEmpty()) {
            mLowPriorityTasks->deQueueLast();
        }
    }

    //notify all thread to close
    PriorityTask nullTask = createPriorityTask(0,nullptr);
    {
        AutoLock l(mTaskMutex);
        mHighPriorityTasks->enQueueLast(nullTask);
        mMidPriorityTasks->enQueueLast(nullTask);
        mLowPriorityTasks->enQueueLast(nullTask);
        mTaskCond->notifyAll();
    }
    
    ThreadPriorityPoolExecutor exe;
    exe.set_pointer(this);
    st(ExecutorRecyler)::getInstance()->add(exe);
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

    bool isWaitForever = (millseconds == 0);

    AutoLock ll(mThreadMutex);
    ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
    while(iterator->hasValue()) {
        PriorityPoolThread handler = iterator->getValue();
        long current = st(System)::currentTimeMillis();
        handler->join(millseconds);
        long interval = (st(System)::currentTimeMillis() - current);
        if(!isWaitForever) {
            millseconds -= interval;
            if(millseconds <= 0) {
                return -WaitTimeout;
            }
        }
        iterator->next();
    }

    return 0;
}

Future _ThreadPriorityPoolExecutor::submit(Runnable task) {
    return submit(PriorityMedium,task);
}

Future _ThreadPriorityPoolExecutor::submit(int level,Runnable task) {
    {
        AutoLock l(mStatusMutex);
        
        if(isShutDown) {
            return nullptr;
        }
    }
    

    FutureTaskStatusListener listener;
    listener.set_pointer(this);

    FutureTask futureTask = createFutureTask(FUTURE_TASK_SUBMIT,task,listener);
    PriorityTask prioTask = createPriorityTask(level,futureTask);
    
    AutoLock l(mTaskMutex);
    switch(prioTask->priority) {
        case st(ThreadPriorityPoolExecutor)::PriorityHigh:
            mHighPriorityTasks->enQueueLast(prioTask);
        break;

        case st(ThreadPriorityPoolExecutor)::PriorityMedium:
            mMidPriorityTasks->enQueueLast(prioTask);
        break;

        case st(ThreadPriorityPoolExecutor)::PriorityLow:
            mLowPriorityTasks->enQueueLast(prioTask);
        break;
    }

    {
        AutoLock l(mTaskMutex);
        mTaskCond->notify();
    }

    return createFuture(futureTask);
}

int _ThreadPriorityPoolExecutor::getThreadsNum() {
    AutoLock ll(mThreadMutex);
    return mThreads->size();
}

void _ThreadPriorityPoolExecutor::onCancel(FutureTask task) {
    {
        AutoLock l(mStatusMutex);

        if(isShutDown) {
            return;
        }
    }
    
    {
        bool isNeedCreate = false;
        AutoLock ll(mThreadMutex);
        ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolThread thread = iterator->getValue();
            
            if(thread->shutdownTask(task)) {
                isNeedCreate = true;
                iterator->remove();
                break;
            }

            iterator->next();
        }
        
        if(isNeedCreate) {
            PriorityPoolThread thread = createPriorityPoolThread(mHighPriorityTasks,
                                                             mMidPriorityTasks,
                                                             mLowPriorityTasks,
                                                             mTaskMutex,
                                                             mTaskCond);
            thread->start();
            mThreads->add(thread);
        }
    }
}

_ThreadPriorityPoolExecutor::~_ThreadPriorityPoolExecutor() {
}

//============== PriorityTask ================
_PriorityTask::_PriorityTask(int level ,FutureTask f) {
    priority = level;
    task = f;
}

}
