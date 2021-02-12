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
class _ScheduledThreadPoolThread;
class _ThreadScheduledPoolExecutor;

DECLARE_SIMPLE_CLASS(WaitingTask) EXTENDS(FutureTask){
public:
    friend class _ScheduledTaskWorker;
    friend class _ScheduledThreadPoolThread;
    friend class _ThreadScheduledPoolExecutor;

    _WaitingTask(Runnable);

    void init(long int interval,int type,int repeat);
    void setExecutor(_ThreadScheduledPoolExecutor *);

    //~_WaitingTask();

    void onComplete();
    
    sp<_WaitingTask> next;
                 
private:
    long int nextTime;
    int mScheduleTaskType;
    long int repeatDelay;
    _ThreadScheduledPoolExecutor *mExecutor;
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
        if(isShutdown() || isTerminated()) {
            return nullptr;
        }
        WaitingTask task = createWaitingTask(r);
        task->init(delay,ScheduletTaskNormal,-1);
        task->setExecutor(this);

        addWaitingTask(task);

        Future future = createFuture(task);
        return future;
    }

    template< class Function, class... Args >
    Future schedule(long delay,Function&& f, Args&&... args) {
        if(isShutdown() || isTerminated()) {
            return nullptr;
        }
        Runnable r = createLambdaRunnable(f,args...);
        WaitingTask task = createWaitingTask(r);
        task->init(delay,ScheduletTaskNormal,-1);
        task->setExecutor(this);
        addWaitingTask(task);
        Future future = createFuture(task);
        return future;
    }
    
#if 0
    template<typename X>
    Future scheduleAtFixedRate( long initialDelay,
                                long period,
                                sp<X> r) {
        if(isShutdown() || isTerminated()) {
            return nullptr;
        }
        WaitingTask task = createWaitingTask(r);
        task->init(initialDelay,ScheduletTaskFixRate,period);
        task->setExecutor(this);
        addWaitingTask(task);
        Future future = createFuture(task);
        return future;
    }

    template< class Function, class... Args >
    Future scheduleAtFixedRate( long initialDelay,
                                long period,
                                Function&& f, Args&&... args ) {
        if(isShutdown() || isTerminated()) {
            return nullptr;
        }
        Runnable r = createLambdaRunnable(f,args...);
        return scheduleAtFixedRate(initialDelay,period,r);                        
    }

    template<typename X>
    Future scheduleWithFixedDelay(long initialDelay,
                                long delay,
                                sp<X> r) {
        if(isShutdown() || isTerminated()) {
            return nullptr;
        }
        WaitingTask task = createWaitingTask(r);
        task->init(initialDelay,ScheduletTaskFixedDelay,delay);

        Future future = createFuture(task);
        return future;
    }

    template< class Function, class... Args >
    Future scheduleWithFixedDelay( long initialDelay,
                                long period,
                                Function&& f, Args&&... args ) {
        if(isShutdown() || isTerminated()) {
            return nullptr;
        }
        Runnable r = createLambdaRunnable(f,args...);
        return scheduleWithFixedDelay(initialDelay,period,r);                        
    }
#endif

    int getThreadsNum();

    void addWaitingTask(WaitingTask);                

private:
    void run();

    WaitingTask newFixedRateWaitingTask(Runnable command,
                                long initialDelay,
                                long period);

    WaitingTask newFixedDelayWaitingTask(Runnable command,
                                long initialDelay,
                                long delay);

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