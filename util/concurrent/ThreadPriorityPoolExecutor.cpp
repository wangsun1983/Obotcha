#include <map>
#include <pthread.h>
#include <stdio.h>

#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "Future.hpp"
#include "Log.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "System.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor(int maxPendingTaskNum, 
                                                        int defaultThreadNum,
                                                        uint32_t maxSubmitTaskWaitTime):_Executor() {
    mTaskMutex = createMutex();
    notEmpty = createCondition();
    notFull = createCondition();

    mMaxPendingTaskNum = maxPendingTaskNum;
    mMaxSubmitTaskWaitTime = maxSubmitTaskWaitTime;

    mThreads = createArrayList<Thread>();

    mHighPriorityTasks = createLinkedList<ExecutorTask>();
    mMidPriorityTasks = createLinkedList<ExecutorTask>();
    mLowPriorityTasks = createLinkedList<ExecutorTask>();

    updateStatus(Executing);

    mRunningTaskMutex = createMutex();
    mRunningTasks = new ExecutorTask[defaultThreadNum];

    for (int i = 0; i < defaultThreadNum; i++) {
        Thread thread = createThread(
            [](int id,ThreadPriorityPoolExecutor &executor) {
                ExecutorTask mCurrentTask = nullptr;
                while (1) {
                    {
                        AutoLock l(executor->mTaskMutex);
                        if (executor->mHighPriorityTasks->size() > 0) {
                            mCurrentTask =
                                executor->mHighPriorityTasks->takeFirst();
                        } else if (executor->mMidPriorityTasks->size() > 0) {
                            mCurrentTask =
                                executor->mMidPriorityTasks->takeFirst();
                        } else if (executor->mLowPriorityTasks->size() > 0) {
                            mCurrentTask =
                                executor->mLowPriorityTasks->takeFirst();
                        }

                        if (executor->isShutDown()) {
                            executor = nullptr;
                            return;
                        }

                        if (mCurrentTask == nullptr) {
                            // executor->mTaskCond->wait(executor->mTaskMutex);
                            executor->notEmpty->wait(executor->mTaskMutex);
                            continue;
                        }
                        executor->notFull->notify();
                    }

                    {
                        AutoLock l(executor->mRunningTaskMutex);
                        executor->mRunningTasks[id] = mCurrentTask;
                    }

                    mCurrentTask->execute();

                    {
                        AutoLock l(executor->mRunningTaskMutex);
                        executor->mRunningTasks[id] = nullptr;
                    }

                    mCurrentTask = nullptr;
                }
            },
            i,
            AutoClone(this));

        thread->start();
        mThreads->add(thread);
    }
}

int _ThreadPriorityPoolExecutor::shutdown() {
    if(isShutDown()) {
        return 0;
    }
    updateStatus(ShutDown);

    {
        AutoLock l(mTaskMutex);
        while (!mHighPriorityTasks->isEmpty()) {
            ExecutorTask task = mHighPriorityTasks->takeLast();
            task->cancel();
        }

        while (!mMidPriorityTasks->isEmpty()) {
            ExecutorTask task = mMidPriorityTasks->takeLast();
            task->cancel();
        }

        while (!mLowPriorityTasks->isEmpty()) {
            ExecutorTask task = mLowPriorityTasks->takeLast();
            task->cancel();
        }

        notEmpty->notifyAll();
        notFull->notifyAll();
    }
    
    {
        AutoLock l(mRunningTaskMutex);
        int size = mThreads->size();
        for(int i = 0;i<size;i++) {
            auto t = mRunningTasks[i];
            if(t != nullptr) {
                t->cancel();
            }
        }
    }

    ForEveryOne(t,mThreads) {
        t->interrupt();
    }

    return 0;
}

bool _ThreadPriorityPoolExecutor::isTerminated() {
    bool isTerminated = true;
    ForEveryOne(t,mThreads) {
        if (t->getStatus() != st(Thread)::Complete) {
            isTerminated = false;
            break;
        }
    }

    /*
    mThreads->foreach ([&isTerminated](Thread &t) {
        if (t->getStatus() != st(Thread)::Complete) {
            isTerminated = false;
            return Global::Break;
        }
        return Global::Continue;
    });*/

    return isTerminated;
}

Future _ThreadPriorityPoolExecutor::submitRunnable(Runnable r) {
    ExecutorTask task = createExecutorTask(r);
    return submitTask(task);
}

Future _ThreadPriorityPoolExecutor::submitTask(ExecutorTask task) {
    if(isShutDown()) {
        return nullptr;
    }

    AutoLock l(mTaskMutex);
    //Runnable r = task->getRunnable();
    switch (task->getPriority()) {
        case High:
            if (mMaxPendingTaskNum != -1 &&
                mHighPriorityTasks->size() == mMaxPendingTaskNum) {
                notFull->wait(mTaskMutex, mMaxSubmitTaskWaitTime);
            }
            mHighPriorityTasks->putLast(task);
            notEmpty->notify();
            break;

        case Medium:
            if (mMaxPendingTaskNum != -1 && mMidPriorityTasks->size() == mMaxPendingTaskNum) {
                notFull->wait(mTaskMutex, mMaxSubmitTaskWaitTime);
            }
            mMidPriorityTasks->putLast(task);
            notEmpty->notify();
            break;

        case Low:
            if (mMaxPendingTaskNum != -1 && mLowPriorityTasks->size() == mMaxPendingTaskNum) {
                notFull->wait(mTaskMutex, mMaxSubmitTaskWaitTime);
            }
            mLowPriorityTasks->putLast(task);
            notEmpty->notify();
            break;

        default:
            return nullptr;
    }

    return createFuture(task);
}

void _ThreadPriorityPoolExecutor::awaitTermination() { 
    awaitTermination(0); 
}

int _ThreadPriorityPoolExecutor::awaitTermination(long millseconds) {
    if(!isShutDown()) {
        return -1;
    }

    bool isWaitForever = (millseconds == 0);
    ListIterator<Thread> iterator = mThreads->getIterator();
    while (iterator->hasValue()) {
        Thread handler = iterator->getValue();
        long current = st(System)::currentTimeMillis();
        handler->join(millseconds);
        long interval = (st(System)::currentTimeMillis() - current);
        if (!isWaitForever) {
            millseconds -= interval;
            if (millseconds <= 0) {
                return -ETIMEDOUT;
            }
        }
        iterator->next();
    }
    return 0;
}

int _ThreadPriorityPoolExecutor::getExecutingThreadNum() { 
    return mThreads->size(); 
}

int _ThreadPriorityPoolExecutor::getPendingTaskNum() {
    AutoLock l(mTaskMutex);
    return mMidPriorityTasks->size() + mLowPriorityTasks->size() + mHighPriorityTasks->size();
}

_ThreadPriorityPoolExecutor::~_ThreadPriorityPoolExecutor() {
    delete []mRunningTasks;
}

} // namespace obotcha
