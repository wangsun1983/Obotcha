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

    int shutdown();

    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    int getPendingTaskNum();
    
    int getExecutingThreadNum();

    ~_ThreadPriorityPoolExecutor();

private:
    Future submitRunnable(Runnable r);
    Future submitTask(ExecutorTask t);

    void onRemoveTask(ExecutorTask task);

    Mutex mTaskMutex;
    Condition notFull;
    Condition notEmpty;
    LinkedList<ExecutorTask> mHighPriorityTasks;
    LinkedList<ExecutorTask> mMidPriorityTasks;
    LinkedList<ExecutorTask> mLowPriorityTasks;

    Mutex mRunningTaskMutex;
    ExecutorTask *mRunningTasks;

    //int mCapacity;
    //int mMaxPendingTaskNum;
    //uint32_t mMaxSubmitTaskWaitTime;
    
    ArrayList<Thread> mThreads;
};

} // namespace obotcha
#endif