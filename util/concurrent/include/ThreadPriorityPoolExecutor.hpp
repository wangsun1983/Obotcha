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
#include "Callable.hpp"
#include "ArrayList.hpp"
#include "ExecutorService.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Error.hpp"
#include "ConcurrentQueue.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(PriorityTask) {
public:
    _PriorityTask(int,FutureTask);

    int priority;

    FutureTask task;
};

class _ThreadPriorityPoolExecutor;
class _PriorityTaskManager;

DECLARE_SIMPLE_CLASS(PriorityPoolThread) EXTENDS(Thread) {
public:
    _PriorityPoolThread(sp<_PriorityTaskManager>,sp<_ThreadPriorityPoolExecutor> exe);
    
    void run();
    
    void onInterrupt();

    void stop();

    //void waitTermination(long);

    bool foceStopTask(FutureTask);

    ~_PriorityPoolThread();

    sp<_PriorityTaskManager> mTaskMgr;

private:
    ArrayList<PriorityTask> mTasks;
    
    Mutex mMutex;
    
    Condition mCondition;

    Condition mWaitTermCondition;

    Mutex mStateMutex;

    PriorityTask mCurrentTask;
    
    Mutex mExecutorMutex;

    sp<_ThreadPriorityPoolExecutor> mExecutor;

    int mState;
    
    mutable volatile bool mStop;
};

DECLARE_SIMPLE_CLASS(PriorityTaskManager) {
public:
    _PriorityTaskManager();

    void addTask(PriorityTask);

    int cancel(FutureTask);

    void cancelAll();

    PriorityTask getTask();

private:
    ConcurrentQueue<PriorityTask> mHighPriorityTasks;
    ConcurrentQueue<PriorityTask> mMediumPriorityTasks;
    ConcurrentQueue<PriorityTask> mLowPriorityTasks;

    Mutex mTaskMutex;
    Condition mTaskCondition;
};

DECLARE_SIMPLE_CLASS(ThreadPriorityPoolExecutor) IMPLEMENTS(ExecutorService)
                                           IMPLEMENTS(FutureTaskStatusListener) {

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

    static const int PriorityLow = 0;
    static const int PriorityMedium = 1;
    static const int PriorityHigh = 2;

private:

    void onCompleteNotify(PriorityPoolThread t);

    PriorityTaskManager mPriorityTaskMgr;

    int mThreadNum;

    Mutex mProtectMutex;
    
    Mutex mDataLock;

    Condition mDataCond;

    bool isShutDown;

    bool isTermination;
    
    Mutex mThreadMutex;
    ArrayList<PriorityPoolThread> mThreads;

    Mutex mWaitMutex;
    
    Condition mWaitCondition;
};

}
#endif