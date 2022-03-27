#ifndef __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__

#include <vector>

#include "AutoLock.hpp"
#include "BlockingLinkedList.hpp"
#include "Condition.hpp"
#include "Executor.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_CLASS(ThreadPoolExecutor) IMPLEMENTS(Executor) {

public:
    friend class _ExecutorTask;

    _ThreadPoolExecutor(int capacity, int threadnum);

    int shutdown();

    bool isTerminated();

    int awaitTermination(long timeout = 0);

    int getThreadsNum();

    int getTasksNum();

    ~_ThreadPoolExecutor();

private:
    Future submitRunnable(Runnable r);
    Future submitTask(ExecutorTask task);
    
    BlockingLinkedList<ExecutorTask> mPool;

    ArrayList<Thread> mHandlers;

    Mutex mRunningTaskMutex;
    ExecutorTask *mRunningTasks;

    Mutex mMutex;
};

} // namespace obotcha
#endif