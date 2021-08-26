#ifndef __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Thread.hpp"
#include "LinkedList.hpp"

namespace obotcha { 

class _WaitingTask;
class _ThreadScheduledPoolExecutor;

DECLARE_CLASS(WaitingTask) IMPLEMENTS(ExecutorTask){
public:
    friend class _ThreadScheduledPoolExecutor;

    _WaitingTask(long int interval,Runnable);

private:
    long int nextTime;
    sp<_WaitingTask> next;
};


DECLARE_CLASS(ThreadScheduledPoolExecutor) IMPLEMENTS(Thread,Executor) {

public:
    _ThreadScheduledPoolExecutor(int capacity = -1);

    ~_ThreadScheduledPoolExecutor();

    int shutdown();

    void awaitTermination();

    int awaitTermination(long timeout);

    bool isShutdown();

    bool isTerminated();
    
    template<typename X>
    Future submitWithInTime(long timeout,long delay,sp<X> r) {
        WaitingTask task = createWaitingTask(delay,r);
        if(addWaitingTaskLocked(task,timeout) == 0) {
            return createFuture(task);
        }
        return nullptr;
    }
    
    template<typename X>
    Future submit(long delay,sp<X> r) {
        return submitWithInTime(0,delay,r);
    }
    
    template< class Function, class... Args >
    Future submit(long delay,Function&& f, Args&&... args) {
        return submitWithInTime(0,delay,createLambdaRunnable(f,args...));
    }

    template< class Function, class... Args >
    Future submitWithInTime(long timeout,long delay,Function&& f, Args&&... args) {
        return submitWithInTime(timeout,delay,createLambdaRunnable(f,args...));
    }

private:

    void run();

    int addWaitingTaskLocked(WaitingTask,long);

    ThreadCachedPoolExecutor mCachedExecutor;

    int mStatus;

    Mutex mTaskMutex;
    Condition notEmpty;
    Condition notFull;
    Condition mTaskWaitCond; 

    int mCount;
    int mCapacity;

    WaitingTask mTaskPool;
};

}
#endif