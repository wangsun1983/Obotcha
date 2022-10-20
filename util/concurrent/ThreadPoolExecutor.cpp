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
#include "ForEveryOne.hpp"

namespace obotcha {

_ThreadPoolExecutor::_ThreadPoolExecutor(int capacity, int threadnum):_Executor() {
    mPool = createBlockingLinkedList<ExecutorTask>(capacity);
    mHandlers = createArrayList<Thread>();
    mRunningTaskMutex = createMutex();
    mRunningTasks = createList<ExecutorTask>(threadnum);
    for (int i = 0; i < threadnum; i++) {
        Thread thread = createThread(
            [this](int id,ThreadPoolExecutor executor) {
                auto exec = executor; //use this to keep executor instance
                while (1) {
                    ExecutorTask mCurrentTask = mPool->takeFirst();

                    if (mCurrentTask == nullptr) {
                        // clear executor to enable executor release.
                        exec = nullptr;
                        return;
                    }

                    {
                        AutoLock l(mRunningTaskMutex);
                        mRunningTasks[id] = mCurrentTask;
                    }

                    mCurrentTask->execute();

                    {
                        AutoLock l(mRunningTaskMutex);
                        mRunningTasks[id] = nullptr;
                    }
                }
            },
            i,
            AutoClone(this));

        thread->start();
        mHandlers->add(thread);
    }

    updateStatus(Executing);
}

Future _ThreadPoolExecutor::submitRunnable(Runnable r) {
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

    ForEveryOne(task,mPool) {
        task->cancel();
    }

    mPool->destroy();

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

    ForEveryOne(t,mHandlers) {
        t->interrupt();
    }

    return 0;
}

bool _ThreadPoolExecutor::isTerminated() {
    ForEveryOne(t,mHandlers) {
        if (t->getStatus() != st(Thread)::Complete) {
            return false;
        }
    }

    return true;
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    if(!isShutDown()) {
        return -1;
    }

    bool isWaitForever = (millseconds == 0);
    TimeWatcher watcher = createTimeWatcher();

    ForEveryOne(handler,mHandlers) {
        watcher->start();
        handler->join(millseconds);
        if (!isWaitForever) {
            millseconds -= watcher->stop();
            if (millseconds <= 0) {
                return -ETIMEDOUT;
            }
        }
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
    //delete []mRunningTasks;
}

} // namespace obotcha
