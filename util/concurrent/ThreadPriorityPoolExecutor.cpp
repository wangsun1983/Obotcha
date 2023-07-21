#include "ThreadPriorityPoolExecutor.hpp"
#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Log.hpp"
#include "System.hpp"
#include "ForEveryOne.hpp"
#include "Synchronized.hpp"
#include "Inspect.hpp"
#include "InfiniteLoop.hpp"

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
            [this](int id,ThreadPriorityPoolExecutor executor) {
                ExecutorTask mCurrentTask = nullptr;
                InfiniteLoop {
                    {
                        AutoLock l(mTaskMutex);
                        if (mHighPriorityTasks->size() > 0) {
                            mCurrentTask = mHighPriorityTasks->takeFirst();
                        } else if (executor->mMidPriorityTasks->size() > 0) {
                            mCurrentTask = mMidPriorityTasks->takeFirst();
                        } else if (executor->mLowPriorityTasks->size() > 0) {
                            mCurrentTask = mLowPriorityTasks->takeFirst();
                        }

                        if (isShutDown()) {
                            return;
                        }

                        if (mCurrentTask == nullptr) {
                            notEmpty->wait(executor->mTaskMutex);
                            continue;
                        }
                        notFull->notify();
                    }

                    Synchronized(mRunningTaskMutex) {
                        executor->mRunningTasks[id] = mCurrentTask;
                    }

                    mCurrentTask->execute();

                    Synchronized(mRunningTaskMutex) {
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
    Inspect(isShutDown(),0)

    updateStatus(ShutDown);

    Synchronized(mTaskMutex) {
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
    
    Synchronized(mRunningTaskMutex) {
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

    return isTerminated;
}

Future _ThreadPriorityPoolExecutor::submitRunnable(Runnable r) {
    ExecutorTask task = createExecutorTask(r,std::bind(&_ThreadPriorityPoolExecutor::onRemoveTask,
                                                       this,
                                                       std::placeholders::_1));
    return submitTask(task);
}

Future _ThreadPriorityPoolExecutor::submitTask(ExecutorTask task) {
    Inspect(isShutDown(),nullptr)

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
    Inspect(!isShutDown(),-1)

    bool isWaitForever = (millseconds == 0);
    ArrayListIterator<Thread> iterator = mThreads->getIterator();
    while (iterator->hasValue()) {
        Thread handler = iterator->getValue();
        long current = st(System)::CurrentTimeMillis();
        handler->join(millseconds);
        long interval = (st(System)::CurrentTimeMillis() - current);
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

void _ThreadPriorityPoolExecutor::onRemoveTask(ExecutorTask task) {
    Inspect(!isExecuting())
    
    AutoLock l(mTaskMutex);
    mMidPriorityTasks->remove(task);
    mLowPriorityTasks->remove(task);
    mHighPriorityTasks->remove(task);
}

_ThreadPriorityPoolExecutor::~_ThreadPriorityPoolExecutor() {
    delete []mRunningTasks;
}

} // namespace obotcha
