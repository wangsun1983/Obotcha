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
#include "ThreadPriorityPoolExecutor.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "System.hpp"
#include "Log.hpp"
#include "Executors.hpp"

namespace obotcha {

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
}

PriorityTask _PriorityPoolThread::getTask() {
    while(1) {
        AutoLock l(mMutex);

        PriorityTask task = nullptr;
        if(highTasks->size() > 0) {
            task = highTasks->deQueueFirst();
            if(task->priority == st(ThreadPriorityPoolExecutor)::PriorityNoUse) {
                highTasks->enQueueLast(task);
                return nullptr;
            }
        }else if(midTasks->size() > 0) {
            task = midTasks->deQueueFirst();
            if(task->priority == st(ThreadPriorityPoolExecutor)::PriorityNoUse) {
                midTasks->enQueueLast(task);
                return nullptr;
            }
        }else if(lowTasks->size() > 0) {
            task = lowTasks->deQueueFirst();
            if(task->priority == st(ThreadPriorityPoolExecutor)::PriorityNoUse) {
                lowTasks->enQueueLast(task);
                return nullptr;
            }
        }

        if(task != nullptr) {
            return task;
        }

        mCond->wait(mMutex);
    }
}

void _PriorityPoolThread::run() {
    while(1) {
        mCurrentTask = getTask();
        
        if(mCurrentTask == nullptr) {
            break;
        }

        if(mCurrentTask->getStatus() == st(Future)::Cancel) {
            continue;
        }
        
        mCurrentTask->onRunning();
        
        Runnable runnable = mCurrentTask->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }
        
        mCurrentTask->onComplete();
        mCurrentTask = nullptr;
    }
}

_PriorityPoolThread::~_PriorityPoolThread() {
}

//============= ThreadPriorityPoolExecutor ================
_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor():_ThreadPriorityPoolExecutor(1) {
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
        AutoLock l(mTaskMutex);
        while(!mHighPriorityTasks->isEmpty()) {
            PriorityTask task = mHighPriorityTasks->deQueueLast();
            task->cancel();
        }

        while(!mMidPriorityTasks->isEmpty()) {
            PriorityTask task = mMidPriorityTasks->deQueueLast();
            task->cancel();
        }

        while(!mLowPriorityTasks->isEmpty()) {
            PriorityTask task = mLowPriorityTasks->deQueueLast();
            task->cancel();
        }
    }

    //notify all thread to close
    PriorityTask exitTask = createPriorityTask(PriorityNoUse,nullptr);
    {
        AutoLock l(mTaskMutex);
        mHighPriorityTasks->enQueueLast(exitTask);
        mMidPriorityTasks->enQueueLast(exitTask);
        mLowPriorityTasks->enQueueLast(exitTask);
        mTaskCond->notifyAll();
    }
    
    st(ExecutorRecyler)::getInstance()->add(AutoClone(this));
}

void _ThreadPriorityPoolExecutor::setAsTerminated() {
    {
        AutoLock l(mStatusMutex);
        isTermination = true;
    }

    mThreads->clear();
}

bool _ThreadPriorityPoolExecutor::isTerminated() {
    AutoLock l(mStatusMutex);
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

    PriorityTask prioTask = createPriorityTask(level,task);
    {
        AutoLock l(mTaskMutex);
        switch(prioTask->priority) {
            case st(ThreadPriorityPoolExecutor)::PriorityHigh:
                mHighPriorityTasks->enQueueLast(prioTask);
                mTaskCond->notify();
            break;

            case st(ThreadPriorityPoolExecutor)::PriorityMedium:
                mMidPriorityTasks->enQueueLast(prioTask);
                mTaskCond->notify();
            break;

            case st(ThreadPriorityPoolExecutor)::PriorityLow:
                mLowPriorityTasks->enQueueLast(prioTask);
                mTaskCond->notify();
            break;
        }
    }

    return createFuture(prioTask);
}

int _ThreadPriorityPoolExecutor::getThreadsNum() {
    AutoLock ll(mThreadMutex);
    return mThreads->size();
}

_ThreadPriorityPoolExecutor::~_ThreadPriorityPoolExecutor() {
}

//============== PriorityTask ================
_PriorityTask::_PriorityTask(int level,Runnable r):_FutureTask(r) {
    priority = level;
}

}
