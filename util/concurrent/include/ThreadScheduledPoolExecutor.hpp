#ifndef __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Thread.hpp"
#include "FutureTask.hpp"
#include "LinkedList.hpp"

namespace obotcha { 

class _WaitingTask;
class _ThreadScheduledPoolExecutor;

DECLARE_SIMPLE_CLASS(WaitingTask) IMPLEMENTS(FutureTask){
public:
    friend class _ThreadScheduledPoolExecutor;

    _WaitingTask(long int interval,Runnable);

private:
    long int nextTime;
    sp<_WaitingTask> next;
};

DECLARE_SIMPLE_CLASS(ThreadScheduledPoolExecutor) IMPLEMENTS(Thread) {

public:
    _ThreadScheduledPoolExecutor();

    ~_ThreadScheduledPoolExecutor();

    int shutdown();

    void awaitTermination();

    int awaitTermination(long timeout);

    bool isShutdown();

    bool isTerminated();
    
    template<typename X>
    Future schedule(long delay,sp<X> r) {
        AutoLock l(mTaskMutex);
        if(mStatus == ShutDown) {
            return nullptr;
        }
        WaitingTask task = createWaitingTask(delay,r);
        addWaitingTaskLocked(task);
        return createFuture(task);
    }

    template< class Function, class... Args >
    Future schedule(long delay,Function&& f, Args&&... args) {
        return schedule(delay,createLambdaRunnable(f,args...));
    }

private:
    enum Status {
        Running,
        ShutDown
    };

    void run();

    void addWaitingTaskLocked(WaitingTask);

    ThreadCachedPoolExecutor mCachedExecutor;

    int mStatus;

    Mutex mTaskMutex;

    Condition mTaskWaitCond; 

    WaitingTask mTaskPool;
};

}
#endif