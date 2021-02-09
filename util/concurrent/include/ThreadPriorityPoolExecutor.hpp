#ifndef __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__
#define __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Error.hpp"
#include "LinkedList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(PriorityTask) EXTENDS(FutureTask) {
public:
    _PriorityTask(int,Runnable);

    int priority;
};

DECLARE_SIMPLE_CLASS(ThreadPriorityPoolExecutor) {

public:
    friend class _PriorityPoolThread;

    _ThreadPriorityPoolExecutor();

    _ThreadPriorityPoolExecutor(int threadnum);

    int execute(Runnable command);

    int execute(int level,Runnable command);

    int shutdown();

    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    Future submit(int level,Runnable task);

    void onCancel(FutureTask);

    int getThreadsNum();

    ~_ThreadPriorityPoolExecutor();
    
    enum Priority {
        PriorityLow = 0,
        PriorityMedium,
        PriorityHigh,
        PriorityNoUse
    };

private:
    Mutex mTaskMutex;
    Condition mTaskCond;
    LinkedList<PriorityTask>mHighPriorityTasks;
    LinkedList<PriorityTask>mMidPriorityTasks;
    LinkedList<PriorityTask>mLowPriorityTasks;

    int mThreadNum;

    Mutex mStatusMutex;

    bool isShutDown;

    bool isTermination;
    
    Mutex mThreadMutex;
    ArrayList<Thread> mThreads;

    Mutex mWaitMutex;
    
    Condition mWaitCondition;

    PriorityTask getTask();
};

}
#endif