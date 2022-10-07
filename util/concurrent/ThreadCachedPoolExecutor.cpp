#include <stdio.h>
#include <unistd.h>
#include <vector>

#include "AutoLock.hpp"
#include "BlockingQueue.hpp"
#include "Error.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "InitializeException.hpp"
#include "Integer.hpp"
#include "Log.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "System.hpp"
#include "Thread.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "TimeWatcher.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

//---------------ThreadCachedPoolExecutor ---------------------
_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int queuesize,
                                                     int minthreadnum,
                                                     int maxthreadnum,
                                                     long timeout):_Executor() {
    if (queuesize == 0 || minthreadnum > maxthreadnum) {
        Trigger(InitializeException, "ThreadCachedPool illeagal param");
    }

    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;

    mHandlers = createArrayList<Thread>();
    mMutex = createMutex();
    mTasks = createBlockingLinkedList<ExecutorTask>(queuesize);
    mRunningTaskMutex = createMutex();
    mRunningTasks = createHashMap<Integer,ExecutorTask>();
    updateStatus(Executing);
    mIdleNum = createAtomicInteger(0);
    handlerId = 0;
}

int _ThreadCachedPoolExecutor::shutdown() {
    if(!isExecuting()) {
        return 0;
    }
    updateStatus(ShutDown);

    //mTasks->freeze();
    //mTasks->foreach ([](const ExecutorTask &t) {
    //    t->cancel();
    //    return Global::Continue;
    //},[this](){
    //    mTasks->destroy();
    //});
    ForEveryOne(task,mTasks) {
        task->cancel();
    }

    mTasks->destroy();
    // notify all thread to close

    //mTasks->unfreeze();

    {
        AutoLock l(mRunningTaskMutex);
        auto iterator = mRunningTasks->getIterator();
        while(iterator->hasValue()) {
            auto value = iterator->getValue();
            value->cancel();
            iterator->next();
        }

        mRunningTasks->clear();
    }

    {
        AutoLock l(mMutex);
        //mHandlers->foreach ([](Thread &t) {
        //    t->interrupt();
        //    return Global::Continue;
        //});
        ForEveryOne(t,mHandlers) {
            t->interrupt();
        }
    }
    return 0;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    AutoLock l(mMutex);
    ListIterator<Thread> iterator = mHandlers->getIterator();
    while (iterator->hasValue()) {
        Thread t = iterator->getValue();
        if (t->getStatus() != st(Thread)::Complete) {
            return false;
        }
        iterator->next();
    }

    return true;
}

void _ThreadCachedPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    if(isExecuting()) {
        return -1;
    }

    bool isWaitForever = (millseconds == 0);

    // ListIterator<Thread> iterator = mHandlers->getIterator();
    ArrayList<Thread> list = createArrayList<Thread>();
    {
        AutoLock l(mMutex);
        list->add(mHandlers);
    }
    auto iterator = list->getIterator();
    TimeWatcher watcher = createTimeWatcher();

    while (iterator->hasValue()) {
        Thread handler = iterator->getValue();
        watcher->start();
        handler->join(millseconds);
        long interval = watcher->stop();

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

int _ThreadCachedPoolExecutor::getThreadsNum() {
    AutoLock l(mMutex);
    return mHandlers->size();
}

int _ThreadCachedPoolExecutor::getTasksNum() {
    return mTasks->size();
}

Future _ThreadCachedPoolExecutor::submitTask(ExecutorTask task) {
    if(!isExecuting()) {
        return nullptr;
    }

    mTasks->putLast(task, mQueueTimeout);
    if (mIdleNum->get() == 0) {
        setUpOneIdleThread();
    }

    return createFuture(task);
}

Future _ThreadCachedPoolExecutor::submitRunnable(Runnable r) {
    ExecutorTask task = createExecutorTask(r);
    return submitTask(task);
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
    //this->shutdown();
    //this->awaitTermination();
}

void _ThreadCachedPoolExecutor::setUpOneIdleThread() {
    if(!isExecuting()) {
        return;
    }

    {
        AutoLock l(mMutex);
        if (mHandlers->size() >= maxThreadNum) {
            return;
        }
    }

    Thread handler = createThread(
        [this](ThreadCachedPoolExecutor executor) {
            handlerId++;
            while (1) {
                auto mCurrentTask =
                    executor->mTasks->takeFirst(executor->mThreadTimeout);
                executor->mIdleNum->subAndGet(1);
                if (mCurrentTask == nullptr) {
                    Thread handler = st(Thread)::current();
                    {
                        AutoLock l(executor->mMutex);
                        executor->mHandlers->remove(handler);
                        executor = nullptr;
                    }
                    return;
                }

                {
                    AutoLock l(mRunningTaskMutex);
                    executor->mRunningTasks->put(createInteger(handlerId),mCurrentTask);
                }

                mCurrentTask->execute();

                {
                    AutoLock l(mRunningTaskMutex);
                    executor->mRunningTasks->remove(createInteger(handlerId));
                }

                executor->mIdleNum->addAndGet(1);
            }
        },
        AutoClone(this));

    handler->start();
    {
        AutoLock l(mMutex);
        mHandlers->add(handler);
    }

    mIdleNum->addAndGet(1);
}

} // namespace obotcha
