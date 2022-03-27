#ifndef __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__

#include <vector>

#include "AutoLock.hpp"
#include "Closeable.hpp"
#include "Condition.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "LinkedList.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "Thread.hpp"
#include "ThreadCachedPoolExecutor.hpp"

namespace obotcha {

class _WaitingTask;
class _ThreadScheduledPoolExecutor;

DECLARE_CLASS(WaitingTask) IMPLEMENTS(ExecutorTask) {
public:
    friend class _ThreadScheduledPoolExecutor;

    _WaitingTask(long int interval, Runnable);
    ~_WaitingTask();

private:
    long int nextTime;
    sp<_WaitingTask> next;
};

DECLARE_CLASS(ThreadScheduledPoolExecutor) IMPLEMENTS(Thread, Executor, Closeable) {

public:
    _ThreadScheduledPoolExecutor(int capacity = -1);

    ~_ThreadScheduledPoolExecutor();

    int shutdown();

    void awaitTermination();

    int awaitTermination(long timeout);

    bool isTerminated();

private:
    Future submitRunnable(Runnable r);
    Future submitTask(ExecutorTask task);
    
    void run();

    void close();

    int addWaitingTaskLocked(WaitingTask, long);

    ThreadCachedPoolExecutor mCachedExecutor;

    Mutex mTaskMutex;
    Condition notEmpty;
    Condition notFull;
    Condition mTaskWaitCond;

    WaitingTask mCurrentTask;

    int mCount;
    int mCapacity;

    WaitingTask mTaskPool;
};

} // namespace obotcha
#endif