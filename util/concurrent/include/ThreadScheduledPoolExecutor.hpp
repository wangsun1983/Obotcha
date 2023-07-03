#ifndef __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__

#include "Object.hpp"
#include "Condition.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"
#include "Closeable.hpp"
#include "ThreadCachedPoolExecutor.hpp"

namespace obotcha {

class _WaitingTask;
class _ThreadScheduledPoolExecutor;

DECLARE_CLASS(WaitingTask) {
public:
    friend class _ThreadScheduledPoolExecutor;

    _WaitingTask(ExecutorTask);
    ~_WaitingTask();

    long int nextTime;
    sp<_WaitingTask> next;
    ExecutorTask task;
};

DECLARE_CLASS(ThreadScheduledPoolExecutor) IMPLEMENTS(Thread, Executor, Closeable) {

public:
    _ThreadScheduledPoolExecutor(int maxPendingTaskNum,
                                 uint32_t maxSubmitTaskWaitTime);

    ~_ThreadScheduledPoolExecutor();

    int shutdown();

    void awaitTermination();

    int awaitTermination(long timeout);

    int getPendingTaskNum();
    
    int getExecutingThreadNum();

    bool isTerminated();

private:
    Future submitTask(ExecutorTask task);
    
    void run();

    void close();

    int addWaitingTaskLocked(WaitingTask, long);

    void onRemoveTask(ExecutorTask task);

    ThreadCachedPoolExecutor mCachedExecutor;

    Mutex mTaskMutex;
    Condition notEmpty;
    Condition notFull;
    Condition mTaskWaitCond;

    WaitingTask mCurrentTask;

    int mCount;

    WaitingTask mTaskPool;
};

} // namespace obotcha
#endif