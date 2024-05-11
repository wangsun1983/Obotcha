#ifndef __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__
#define __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__

#include "Object.hpp"

#include "ArrayList.hpp"
#include "Condition.hpp"
#include "Executor.hpp"
#include "Future.hpp"
#include "LinkedList.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_CLASS(ThreadPriorityPoolExecutor) IMPLEMENTS(Executor) {
public:
    _ThreadPriorityPoolExecutor(size_t maxPendingTaskNum, 
                                long defaultThreadNum,
                                uint32_t maxSubmitTaskWaitTime);

    int shutdown() final;

    bool isTerminated() override;

    int awaitTermination(long timeout = st(Concurrent)::kWaitForEver) final;

    size_t getPendingTaskNum() override;
    
    size_t getExecutingThreadNum() override;

    ~_ThreadPriorityPoolExecutor() override;

private:
    Future submitRunnable(Runnable r);
    Future submitTask(ExecutorTask t) override;

    void onRemoveTask(ExecutorTask task) override;

    Mutex mTaskMutex = Mutex::New();
    Condition notFull = Condition::New();
    Condition notEmpty = Condition::New();
    LinkedList<ExecutorTask> mHighPriorityTasks = LinkedList<ExecutorTask>::New();
    LinkedList<ExecutorTask> mMidPriorityTasks = LinkedList<ExecutorTask>::New();
    LinkedList<ExecutorTask> mLowPriorityTasks = LinkedList<ExecutorTask>::New();
    Mutex mRunningTaskMutex = Mutex::New();
    ArrayList<Thread> mThreads = ArrayList<Thread>::New();

    ExecutorTask *mRunningTasks;
};

} // namespace obotcha
#endif