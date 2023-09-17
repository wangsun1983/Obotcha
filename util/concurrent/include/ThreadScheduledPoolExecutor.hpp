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

    explicit _WaitingTask(ExecutorTask);
    ~_WaitingTask() override = default;

    long int nextTime;
    sp<_WaitingTask> next = nullptr;
    ExecutorTask task;
};

DECLARE_CLASS(ThreadScheduledPoolExecutor) IMPLEMENTS(Thread, Executor, Closeable) {

public:
    _ThreadScheduledPoolExecutor(int maxPendingTaskNum,
                                 uint32_t maxSubmitTaskWaitTime);

    ~_ThreadScheduledPoolExecutor() override;

    int shutdown() final;

    int awaitTermination(long timeout = 0) final;

    size_t getPendingTaskNum() override;
    
    size_t getExecutingThreadNum() override;

    bool isTerminated() override;

private:
    Future submitTask(ExecutorTask task) override;
    
    void run() override;

    void close() override;

    int addWaitingTaskLocked(WaitingTask, long);

    void onRemoveTask(ExecutorTask task) override;

    ThreadCachedPoolExecutor mCachedExecutor;

    Mutex mTaskMutex = createMutex();
    Condition notEmpty = createCondition();
    Condition notFull = createCondition();
    Condition mTaskWaitCond = createCondition();
    int mCount = 0;
    WaitingTask mCurrentTask = nullptr;
    WaitingTask mTaskPool = nullptr;
};

} // namespace obotcha
#endif