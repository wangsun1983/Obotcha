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
    _ThreadPriorityPoolExecutor(int maxPendingTaskNum, 
                                int defaultThreadNum,
                                uint32_t maxSubmitTaskWaitTime);

    int shutdown() final;

    bool isTerminated() override;

    int awaitTermination(long timeout = 0) final;

    size_t getPendingTaskNum() override;
    
    size_t getExecutingThreadNum() override;

    ~_ThreadPriorityPoolExecutor() override;

private:
    Future submitRunnable(Runnable r);
    Future submitTask(ExecutorTask t) override;

    void onRemoveTask(ExecutorTask task) override;

    Mutex mTaskMutex = createMutex();
    Condition notFull = createCondition();
    Condition notEmpty = createCondition();
    LinkedList<ExecutorTask> mHighPriorityTasks = createLinkedList<ExecutorTask>();
    LinkedList<ExecutorTask> mMidPriorityTasks = createLinkedList<ExecutorTask>();
    LinkedList<ExecutorTask> mLowPriorityTasks = createLinkedList<ExecutorTask>();
    Mutex mRunningTaskMutex = createMutex();
    ArrayList<Thread> mThreads = createArrayList<Thread>();

    ExecutorTask *mRunningTasks;
};

} // namespace obotcha
#endif