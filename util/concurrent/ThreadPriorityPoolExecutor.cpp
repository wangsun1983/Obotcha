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

//============= ThreadPriorityPoolExecutor ================
_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor():_ThreadPriorityPoolExecutor(1) {
    //do nothing
}

_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor(int threadnum) {
    mStatusMutex = createMutex("PriorityStatusMutex");
    mTaskMutex = createMutex("PriorityData");
    mTaskCond = createCondition();

    mThreadMutex = createMutex("PriorityThread Mutex");
    mThreads = createArrayList<Thread>();

    mHighPriorityTasks = createLinkedList<PriorityTask>();
    mMidPriorityTasks = createLinkedList<PriorityTask>();
    mLowPriorityTasks = createLinkedList<PriorityTask>();

    mThreadNum = threadnum;
    for(int i = 0;i < threadnum;i++) {
        Thread thread = createThread([this](){
            PriorityTask mCurrentTask = nullptr;
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
        });
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

    ListIterator<Thread> iterator = mThreads->getIterator();
    while(iterator->hasValue()) {
        Thread handler = iterator->getValue();
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

PriorityTask _ThreadPriorityPoolExecutor::getTask() {
    while(1) {
        AutoLock l(mTaskMutex);

        PriorityTask task = nullptr;
        if(mHighPriorityTasks->size() > 0) {
            task = mHighPriorityTasks->deQueueFirst();
            if(task->priority == st(ThreadPriorityPoolExecutor)::PriorityNoUse) {
                mHighPriorityTasks->enQueueLast(task);
                return nullptr;
            }
        }else if(mMidPriorityTasks->size() > 0) {
            task = mMidPriorityTasks->deQueueFirst();
            if(task->priority == st(ThreadPriorityPoolExecutor)::PriorityNoUse) {
                mMidPriorityTasks->enQueueLast(task);
                return nullptr;
            }
        }else if(mLowPriorityTasks->size() > 0) {
            task = mLowPriorityTasks->deQueueFirst();
            if(task->priority == st(ThreadPriorityPoolExecutor)::PriorityNoUse) {
                mLowPriorityTasks->enQueueLast(task);
                return nullptr;
            }
        }

        if(task != nullptr) {
            return task;
        }

        mTaskCond->wait(mTaskMutex);
    }
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
