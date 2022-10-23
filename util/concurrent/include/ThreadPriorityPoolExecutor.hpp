#ifndef __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__
#define __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__

#include <map>
#include <pthread.h>

#include "ArrayList.hpp"
#include "Condition.hpp"
#include "Error.hpp"
#include "Executor.hpp"
#include "Future.hpp"
#include "LinkedList.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
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

    int getThreadsNum();

    ~_ThreadPriorityPoolExecutor();

private:
    Future submitRunnable(Runnable r);
    Future submitTask(ExecutorTask t);

    Mutex mTaskMutex;
    Condition notFull;
    Condition notEmpty;
    LinkedList<ExecutorTask> mHighPriorityTasks;
    LinkedList<ExecutorTask> mMidPriorityTasks;
    LinkedList<ExecutorTask> mLowPriorityTasks;

    Mutex mRunningTaskMutex;
    ExecutorTask *mRunningTasks;

    //int mCapacity;
    int mMaxPendingTaskNum;
    uint32_t mMaxSubmitTaskWaitTime;
    
    ArrayList<Thread> mThreads;
};

} // namespace obotcha
#endif