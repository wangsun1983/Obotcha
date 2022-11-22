#include <stdio.h>
#include <stdlib.h>


#include "ThreadPoolExecutor.hpp"
#include "Log.hpp"
#include "TimeWatcher.hpp"
#include "ForEveryOne.hpp"
#include "Synchronized.hpp"
#include "Inspect.hpp"

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
                while (1) {
                    ExecutorTask mCurrentTask = mPendingTasks->takeFirst();

                    Inspect(mCurrentTask == nullptr);

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
    Inspect(isShutDown(),nullptr);

    task->setPending();

    if (mPendingTasks->putLast(task, mMaxSubmitTaskWaitTime)) {
        return createFuture(task);
    }

    return nullptr;
}


int _ThreadPoolExecutor::shutdown() {
    Inspect(!isExecuting(),0);

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
    Inspect(!isShutDown(),-1);

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

void _ThreadPoolExecutor::onRemoveTask(ExecutorTask task) {
    Inspect(!isExecuting());

    mPendingTasks->remove(task);
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    if(!isShutDown()) {
        LOG(ERROR)<<"ThreadPoolExecutor release without shutdown!!!!";
        shutdown();
        awaitTermination();
    }
}

} // namespace obotcha
