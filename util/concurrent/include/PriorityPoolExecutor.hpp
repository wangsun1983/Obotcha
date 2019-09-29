#ifndef __PRIORITY_POOL_EXECUTOR_SERVICE_H__
#define __PRIORITY_POOL_EXECUTOR_SERVICE_H__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "Executor.hpp"
#include "Callable.hpp"
#include "ArrayList.hpp"
#include "ExecutorService.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Error.hpp"

namespace obotcha {

enum TaskPriority {
    TaskPriorityLow,
    TaskPriorityMedium,
    TaskPriorityHigh
};

DECLARE_SIMPLE_CLASS(PriorityTask) {
public:
    _PriorityTask(int,FutureTask);

    int priority;

    FutureTask task;
};

class _PriorityPoolExecutor;

DECLARE_SIMPLE_CLASS(PriorityPoolThread) EXTENDS(Thread) {
public:
    _PriorityPoolThread(ArrayList<PriorityTask>,Mutex,Condition,_PriorityPoolExecutor *exe);
    
    void run();
    
    void onInterrupt();

    void stop();

    void waitTermination(long);

    void onExecutorDestroy();

    ~_PriorityPoolThread();

private:
    ArrayList<PriorityTask> mTasks;
    
    Mutex mMutex;
    
    Condition mCondition;

    Condition mWaitTermCondition;

    Mutex mStateMutex;

    PriorityTask mCurrentTask;
    
    Mutex mExecutorMutex;

    _PriorityPoolExecutor *mExecutor;

    int mState;
    
    mutable volatile bool mStop;
};

DECLARE_SIMPLE_CLASS(PriorityPoolExecutor) IMPLEMENTS(ExecutorService) {

public:
    friend class _PriorityPoolThread;

    _PriorityPoolExecutor();

    _PriorityPoolExecutor(int threadnum);

    int execute(Runnable command);

    int execute(int level,Runnable command);

    int shutdown();

    bool isShutdown();

    bool isTerminated();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    Future submit(int level,Runnable task);

    int getThreadsNum();

    ~_PriorityPoolExecutor();

private:

    void onHandlerRelease();

    int mThreadNum;

    Mutex mProtectMutex;
    
    Mutex mDataLock;

    Condition mDataCond;

    bool isShutDown;

    bool isTermination;
    
    ArrayList<PriorityTask> mPriorityTasks;

    ArrayList<PriorityPoolThread> mThreads;
};

}
#endif