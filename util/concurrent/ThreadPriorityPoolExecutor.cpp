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
    mTaskMutex = createMutex("PriorityData");
    mTaskCond = createCondition();

    mThreadMutex = createMutex("PriorityThread Mutex");
    mThreads = createArrayList<Thread>();

    mHighPriorityTasks = createLinkedList<FutureTask>();
    mMidPriorityTasks = createLinkedList<FutureTask>();
    mLowPriorityTasks = createLinkedList<FutureTask>();

    mThreadNum = threadnum;

    mStatus = createAtomicInteger(Running);

    for(int i = 0;i < threadnum;i++) {
        Thread thread = createThread([](Mutex taskMutex,
                                        Condition taskCond,
                                        LinkedList<FutureTask> high,
                                        LinkedList<FutureTask> mid,
                                        LinkedList<FutureTask>low,
                                        AtomicInteger status){
            FutureTask mCurrentTask = nullptr;
            while(1) {
                {
                    AutoLock l(taskMutex);

                    if(high->size() > 0) {
                        mCurrentTask = high->deQueueFirst();
                    }else if(mid->size() > 0) {
                        mCurrentTask = mid->deQueueFirst();
                    }else if(low->size() > 0) {
                        mCurrentTask = low->deQueueFirst();
                    }

                    if(status->get() == st(ThreadPriorityPoolExecutor)::ShutDown) {
                        return;
                    }

                    if(mCurrentTask == nullptr) {
                        taskCond->wait(taskMutex);
                        continue;
                    }
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
        },mTaskMutex,mTaskCond,mHighPriorityTasks,mMidPriorityTasks,mLowPriorityTasks,mStatus);

        thread->start();
        mThreads->add(thread);
    }

}

int _ThreadPriorityPoolExecutor::execute(Runnable r) {
    return execute(PriorityMedium,r);
}

int _ThreadPriorityPoolExecutor::shutdown() {
    if(mStatus->get() == ShutDown) {
        return -InvalidStatus;
    }

    mStatus->set(ShutDown);

    {
        AutoLock l(mTaskMutex);
        while(!mHighPriorityTasks->isEmpty()) {
            FutureTask task = mHighPriorityTasks->deQueueLast();
            task->cancel();
        }

        while(!mMidPriorityTasks->isEmpty()) {
            FutureTask task = mMidPriorityTasks->deQueueLast();
            task->cancel();
        }

        while(!mLowPriorityTasks->isEmpty()) {
            FutureTask task = mLowPriorityTasks->deQueueLast();
            task->cancel();
        }
    }

    {
        AutoLock l(mThreadMutex);
        ListIterator<Thread> iterator = mThreads->getIterator();
        while(iterator->hasValue()){
            Thread thread = iterator->getValue();
            thread->interrupt();
            iterator->next();
        }
    }

    AutoLock l(mTaskMutex);
    mTaskCond->notifyAll();
}

bool _ThreadPriorityPoolExecutor::isShutDown() {
    return mStatus->get() == ShutDown;
}

bool _ThreadPriorityPoolExecutor::isTerminated() {
    AutoLock l(mThreadMutex);
    ListIterator<Thread> iterator = mThreads->getIterator();
    while(iterator->hasValue()){
        Thread thread = iterator->getValue();
        if(thread->getStatus() != st(Thread)::Complete) {
            return false;
        }
        iterator->next();
    }

    return true;
}

void _ThreadPriorityPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadPriorityPoolExecutor::awaitTermination(long millseconds) {
    if(mStatus->get() != ShutDown) {
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

int _ThreadPriorityPoolExecutor::getThreadsNum() {
    AutoLock ll(mThreadMutex);
    return mThreads->size();
}

_ThreadPriorityPoolExecutor::~_ThreadPriorityPoolExecutor() {
}

}
