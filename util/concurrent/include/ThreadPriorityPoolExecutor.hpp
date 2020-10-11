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
#include "LinkedList.hpp"

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
    _PriorityPoolThread(LinkedList<PriorityTask> high,
                        LinkedList<PriorityTask> mid,
                        LinkedList<PriorityTask> low,
                        Mutex listLock,
                        Condition listcond);
    
    void run();
    
    void onInterrupt();

    void stop();

    bool shutdownTask(FutureTask task);

    ~_PriorityPoolThread();


private:
    Mutex mMutex;
    Condition mCond;
    
    Mutex mCurrentTaskMutex;
    PriorityTask mCurrentTask;
    LinkedList<PriorityTask> highTasks;
    LinkedList<PriorityTask> midTasks;
    LinkedList<PriorityTask> lowTasks;
    
    PriorityTask getTask();
    
    mutable volatile bool mStop;
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

    void setAsTerminated();

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
    ArrayList<PriorityPoolThread> mThreads;

    Mutex mWaitMutex;
    
    Condition mWaitCondition;
};

}
#endif