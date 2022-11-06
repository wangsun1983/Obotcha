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
#include "Log.hpp"
#include "Synchronized.hpp"

namespace obotcha {

_ThreadPoolExecutor::_ThreadPoolExecutor(int maxPendingTaskNum,
                                         int defalutThreadNum,
                                         uint32_t maxSubmitTaskWaitTime):_Executor() {
    mPendingTasks = createBlockingLinkedList<ExecutorTask>(maxPendingTaskNum);
    mHandlers = createArrayList<Thread>();
    mRunningTaskMutex = createMutex();
    mRunningTasks = createList<ExecutorTask>(defalutThreadNum);
    mMaxSubmitTaskWaitTime = maxSubmitTaskWaitTime;

    for (int i = 0; i < defalutThreadNum; i++) {
        Thread thread = createThread(
            [this](int id,ThreadPoolExecutor executor) {
                auto exec = executor; //use this to keep executor instance
                while (1) {
                    ExecutorTask mCurrentTask = mPendingTasks->takeFirst();

                    if (mCurrentTask == nullptr) {
                        // clear executor to enable executor release.
                        exec = nullptr;
                        return;
                    }

                    Synchronized(mRunningTaskMutex) {
                        mRunningTasks[id] = mCurrentTask;
                    }

                    mCurrentTask->execute();

                    Synchronized(mRunningTaskMutex) {
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

Future _ThreadPoolExecutor::submitTask(ExecutorTask task) {
    if(isShutDown()) {
        return nullptr;
    }

    task->setPending();

    if (mPendingTasks->putLast(task, mMaxSubmitTaskWaitTime)) {
        return createFuture(task);
    }

    return nullptr;
}


int _ThreadPoolExecutor::shutdown() {
    if(!isExecuting()) {
        return 0;
    }

    updateStatus(ShutDown);

    ForEveryOne(task,mPendingTasks) {
        task->cancel();
    }

    mPendingTasks->destroy();

    Synchronized(mRunningTaskMutex) {
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

int _ThreadPoolExecutor::getExecutingThreadNum() {
    return mHandlers->size();
}

int _ThreadPoolExecutor::getPendingTaskNum() {
    return mPendingTasks->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    //delete []mRunningTasks;
    if(!isShutDown()) {
        LOG(ERROR)<<"ThreadPoolExecutor release without shutdown!!!!";
        shutdown();
        awaitTermination();
    }
}

} // namespace obotcha
