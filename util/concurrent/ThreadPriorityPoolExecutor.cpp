#include <stdio.h>
#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "System.hpp"
#include "Log.hpp"

namespace obotcha {

//============= ThreadPriorityPoolExecutor ================
_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor(int threadnum) {
    mTaskMutex = createMutex();
    mTaskCond = createCondition();

    mThreads = createArrayList<Thread>();

    mHighPriorityTasks = createLinkedList<ExecutorTask>();
    mMidPriorityTasks = createLinkedList<ExecutorTask>();
    mLowPriorityTasks = createLinkedList<ExecutorTask>();

    mStatus = Running;

    for(int i = 0;i < threadnum;i++) {
        Thread thread = createThread([](ThreadPriorityPoolExecutor &executor){
            ExecutorTask mCurrentTask = nullptr;
            while(1) {
                {
                    AutoLock l(executor->mTaskMutex);
                    if(executor->mHighPriorityTasks->size() > 0) {
                        mCurrentTask = executor->mHighPriorityTasks->takeFirst();
                    }else if(executor->mMidPriorityTasks->size() > 0) {
                        mCurrentTask = executor->mMidPriorityTasks->takeFirst();
                    }else if(executor->mLowPriorityTasks->size() > 0) {
                        mCurrentTask = executor->mLowPriorityTasks->takeFirst();
                    }

                    if(executor->mStatus == st(ThreadPriorityPoolExecutor)::ShutDown) {
                        executor = nullptr;
                        return;
                    }

                    if(mCurrentTask == nullptr) {
                        executor->mTaskCond->wait(executor->mTaskMutex);
                        continue;
                    }
                }

                mCurrentTask->execute();
                mCurrentTask = nullptr;
            }
        },AutoClone(this));

        thread->start();
        mThreads->add(thread);
    }
}

int _ThreadPriorityPoolExecutor::execute(Runnable r) {
    return execute(Medium,r);
}

int _ThreadPriorityPoolExecutor::shutdown() {
    {
        AutoLock l(mTaskMutex);
        if(mStatus == ShutDown) {
            return -InvalidStatus;
        }

        mStatus = ShutDown;

        while(!mHighPriorityTasks->isEmpty()) {
            ExecutorTask task = mHighPriorityTasks->takeLast();
            task->cancel();
        }

        while(!mMidPriorityTasks->isEmpty()) {
            ExecutorTask task = mMidPriorityTasks->takeLast();
            task->cancel();
        }

        while(!mLowPriorityTasks->isEmpty()) {
            ExecutorTask task = mLowPriorityTasks->takeLast();
            task->cancel();
        }
        mTaskCond->notifyAll();
    }

    mThreads->foreach([](Thread &t){
        t->interrupt();
        return Global::Continue;
    });

    return 0;
}

bool _ThreadPriorityPoolExecutor::isShutDown() {
    AutoLock l(mTaskMutex);
    return mStatus == ShutDown;
}

bool _ThreadPriorityPoolExecutor::isTerminated() {
    bool isTerminated = true;
    mThreads->foreach([&isTerminated](Thread &t) {
        if(t->getStatus() != st(Thread)::Complete) {
            isTerminated = false;
            return Global::Break;
        }
        return Global::Continue;
    });

    return isTerminated;
}

void _ThreadPriorityPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadPriorityPoolExecutor::awaitTermination(long millseconds) {
    {
        AutoLock l(mTaskMutex);
        if(mStatus != ShutDown) {
            return -InvalidStatus;
        }
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
    return submit(Medium,task);
}

int _ThreadPriorityPoolExecutor::getThreadsNum() {
    return mThreads->size();
}

_ThreadPriorityPoolExecutor::~_ThreadPriorityPoolExecutor() {
}

}
