#include <stdio.h>
#include <stdlib.h>

#include "Error.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "Log.hpp"
#include "System.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "TimeWatcher.hpp"

namespace obotcha {

_ThreadPoolExecutor::_ThreadPoolExecutor(int capacity, int threadnum):_Executor() {
    mPool = createBlockingLinkedList<ExecutorTask>(capacity);
    mHandlers = createArrayList<Thread>();
    mRunningTaskMutex = createMutex();
    mRunningTasks = new ExecutorTask[threadnum];
    for (int i = 0; i < threadnum; i++) {
        Thread thread = createThread(
            [](int id,ThreadPoolExecutor executor) {
                while (1) {
                    ExecutorTask mCurrentTask = executor->mPool->takeFirst();

                    if (mCurrentTask == nullptr) {
                        // clear executor to enable executor release.
                        executor = nullptr;
                        return;
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
                }
            },
            i,
            AutoClone(this));

        thread->start();
        mHandlers->add(thread);
    }

    mMutex = createMutex();
    updateStatus(Executing);
}

Future _ThreadPoolExecutor::submitRunnable(Runnable r) {
    if(isShutDown()) {
        return nullptr;
    }

    return submitTask(createExecutorTask(r));
}

Future _ThreadPoolExecutor::submitTask(ExecutorTask task) {
    if(isShutDown()) {
        return nullptr;
    }

    if (mPool->putLast(task, mQueueTimeout)) {
        return createFuture(task);
    }

    return nullptr;
}


int _ThreadPoolExecutor::shutdown() {
    if(!isExecuting()) {
        return 0;
    }

    updateStatus(ShutDown);

    //mPool->freeze();
    mPool->foreach ([](const ExecutorTask &task) {
        task->cancel();
        return Global::Continue;
    },[this]() {
      mPool->destroy();
    });

    //mPool->unfreeze();

    {
        AutoLock l(mRunningTaskMutex);
        int size = mHandlers->size();
        for(int i = 0;i<size;i++) {
            auto t = mRunningTasks[i];
            if(t != nullptr) {
                t->cancel();
            }
        }
    }

    // interrupt all thread
    mHandlers->foreach ([](Thread t) {
        t->interrupt();
        return Global::Continue;
    });

    return 0;
}

bool _ThreadPoolExecutor::isTerminated() {
    bool isAllTerminated = true;
    mHandlers->foreach ([&isAllTerminated](Thread &t) {
        if (t->getStatus() != st(Thread)::Complete) {
            isAllTerminated = false;
            return Global::Break;
        }
        return Global::Continue;
    });

    return isAllTerminated;
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    if(!isShutDown()) {
        return -1;
    }

    bool isWaitForever = (millseconds == 0);
    ListIterator<Thread> iterator = mHandlers->getIterator();
    TimeWatcher watcher = createTimeWatcher();

    while (iterator->hasValue()) {
        Thread handler = iterator->getValue();
        watcher->start();
        handler->join(millseconds);
        if (!isWaitForever) {
            millseconds -= watcher->stop();
            if (millseconds <= 0) {
                return -ETIMEDOUT;
            }
        }
        iterator->next();
    }

    return 0;
}

int _ThreadPoolExecutor::getThreadsNum() {
    return mHandlers->size();
}

int _ThreadPoolExecutor::getTasksNum() {
    return mPool->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    delete []mRunningTasks;
}

} // namespace obotcha
