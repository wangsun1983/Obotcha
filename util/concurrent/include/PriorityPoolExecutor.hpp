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
#include "Condition.hpp"
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

DECLARE_SIMPLE_CLASS(PriorityPoolHandler) IMPLEMENTS(Runnable) {

public:

    _PriorityPoolHandler(ArrayList<PriorityTask> pool,Mutex,Condition,sp<_PriorityPoolExecutor> executor);
    
    void run();
    
    void stop();

    void onInterrupt();

    bool shutdownTask(FutureTask);

    ~_PriorityPoolHandler();

private:
    Mutex mFutureMutex;
    Condition mFutureCond;
    ArrayList<PriorityTask> mPool;

    int state;

    bool mIdleWait;

    Mutex mStateMutex;

    Condition mWaitCond;

    bool isWaitTerminate;

    FutureTask mCurrentTask;

    mutable volatile bool mStop;

    Thread mThread;

    sp<_PriorityPoolExecutor> mExecutor;

    Mutex mExecutorMutex;
};


DECLARE_SIMPLE_CLASS(PriorityPoolExecutor) IMPLEMENTS(ExecutorService) 
                                           IMPLEMENTS(FutureTaskStatusListener) {

public:

    friend class _PriorityPoolHandler;

	_PriorityPoolExecutor(int threadnum);

	_PriorityPoolExecutor();

    int shutdown();

    int execute(Runnable command);

    bool isShutdown();

    bool isTerminated();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    Future submit(int level,Runnable task);

    int getThreadsNum();

    void onCancel(FutureTask);

    ~_PriorityPoolExecutor();

private:
    void onCompleteNotify(PriorityPoolHandler h);

    //------------
    Mutex mFutureTaskMutex;
    Condition mFutureCond;
    ArrayList<PriorityTask> mPool;
    
    Mutex mHandlersMutex;
    ArrayList<PriorityPoolHandler> mHandlers;

    bool mIsShutDown;

    bool mIsTerminated;

    //bool isDynamic;
    int mThreadNum;

    void init(int threadnum);

    Mutex mProtectMutex;

    Mutex mWaitMutex;
    Condition mWaitCond;
};


}
#endif