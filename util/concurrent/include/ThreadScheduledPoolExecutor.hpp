#ifndef __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "ArrayList.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "HashMap.hpp"
#include "Thread.hpp"
#include "ArrayList.hpp"
#include "FutureTask.hpp"

enum ScheduledTaskType {
    ScheduletTaskNormal = 0, //normal schedule task
    ScheduletTaskFixRate, //loop time record from task start
    ScheduletTaskFixedDelay //loop time record from task complete
};

namespace obotcha { 

class _WaitingTask;
class _ThreadScheduledPoolExecutor;

DECLARE_SIMPLE_CLASS(WaitingTask) EXTENDS(FutureTask){
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
    
    void setAsTerminated();

    bool isTerminated();
    
    template<typename X>
    Future schedule(long delay,sp<X> r) {
        if(isShutdown()) {
            return nullptr;
        }
        WaitingTask task = createWaitingTask(delay,r);
        addWaitingTask(task);
        return createFuture(task);
    }

    template< class Function, class... Args >
    Future schedule(long delay,Function&& f, Args&&... args) {
        if(isShutdown()) {
            return nullptr;
        }
        Runnable r = createLambdaRunnable(f,args...);
        return schedule(delay,r);
    }

    void addWaitingTask(WaitingTask);                

private:
    void run();

    ThreadCachedPoolExecutor mCachedExecutor;

    bool mIsShutDown;

    bool mIsTerminated;

    Mutex mStatusMutex;

    void init(int size,bool isDyn);

    Mutex mTaskMutex;
    //WaitingTask mRoot;
    Condition mTaskWaitCond; 

    WaitingTask mTaskPool;
};

}
#endif