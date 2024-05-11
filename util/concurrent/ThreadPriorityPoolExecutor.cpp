#include "ThreadPriorityPoolExecutor.hpp"
#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Log.hpp"
#include "System.hpp"
#include "ForEveryOne.hpp"
#include "Synchronized.hpp"
#include "Inspect.hpp"

namespace obotcha {

_ThreadPriorityPoolExecutor::_ThreadPriorityPoolExecutor(size_t maxPendingTaskNum, 
                                                        long defaultThreadNum,
                                                        uint32_t maxSubmitTaskWaitTime):_Executor() {
    mMaxPendingTaskNum = maxPendingTaskNum;
    mDefaultThreadNum = defaultThreadNum;
    mMaxSubmitTaskWaitTime = maxSubmitTaskWaitTime;

    updateStatus(st(Concurrent)::Status::Running);
    mRunningTasks = new ExecutorTask[defaultThreadNum];

    for (int i = 0; i < defaultThreadNum; i++) {
        Thread thread = Thread::New(
            [this](int id,ThreadPriorityPoolExecutor executor) {
                ExecutorTask mCurrentTask = nullptr;
                while(true) {
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
    updateStatus(st(Concurrent)::Status::ShutDown);

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
        size_t size = mThreads->size();
        for(size_t i = 0;i<size;i++) {
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
        if (t->getStatus() != st(Concurrent)::Status::Complete) {
            isTerminated = false;
            break;
        }
    }

    return isTerminated;
}

Future _ThreadPriorityPoolExecutor::submitRunnable(Runnable r) {
    ExecutorTask task = ExecutorTask::New(r,std::bind(&_ThreadPriorityPoolExecutor::onRemoveTask,
                                                       this,
                                                       std::placeholders::_1));
    return submitTask(task);
}

Future _ThreadPriorityPoolExecutor::submitTask(ExecutorTask task) {
    Inspect(isShutDown(),nullptr)
    task->setPending();
    AutoLock l(mTaskMutex);
    switch (task->getPriority()) {
        case st(Concurrent)::TaskPriority::High:
            if (mMaxPendingTaskNum != 0 &&
                mHighPriorityTasks->size() == mMaxPendingTaskNum) {
                notFull->wait(mTaskMutex, mMaxSubmitTaskWaitTime);
            }
            mHighPriorityTasks->putLast(task);
            notEmpty->notify();
            break;

        case st(Concurrent)::TaskPriority::Medium:
            if (mMaxPendingTaskNum != 0 && mMidPriorityTasks->size() == mMaxPendingTaskNum) {
                notFull->wait(mTaskMutex, mMaxSubmitTaskWaitTime);
            }
            mMidPriorityTasks->putLast(task);
            notEmpty->notify();
            break;

        case st(Concurrent)::TaskPriority::Low:
            if (mMaxPendingTaskNum != 0 && mLowPriorityTasks->size() == mMaxPendingTaskNum) {
                notFull->wait(mTaskMutex, mMaxSubmitTaskWaitTime);
            }
            mLowPriorityTasks->putLast(task);
            notEmpty->notify();
            break;
    }

    return Future::New(task);
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

size_t _ThreadPriorityPoolExecutor::getExecutingThreadNum() { 
    return mThreads->size(); 
}

size_t _ThreadPriorityPoolExecutor::getPendingTaskNum() {
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
