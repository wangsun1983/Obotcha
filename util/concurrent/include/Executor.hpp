#ifndef __OBOTCHA_EXECUTOR_HPP__
#define __OBOTCHA_EXECUTOR_HPP__

#include "Condition.hpp"
#include "InterruptedException.hpp"
#include "Mutex.hpp"
#include "OStdInstanceOf.hpp"
#include "Runnable.hpp"
#include "TimeOutException.hpp"
#include "Mutex.hpp"
#include "AtomicInteger.hpp"
#include "ThreadLocal.hpp"

namespace obotcha {
class _ExecutorTask;
class _Future;

DECLARE_CLASS(Executor) {
public:
    enum Status {
        Idle = 0,
        Executing,
        ShutDown,
    };

    enum Priority { 
        Low = 0, 
        Medium, 
        High, 
        NoUse 
    };
    
    _Executor();
    
    bool isExecuting();
    bool isShutDown();

    virtual int shutdown() = 0;

    virtual bool isTerminated() = 0;

    virtual int awaitTermination(long timeout = 0) = 0;

    template <typename T>
    sp<_Future> submit(sp<T> r) {
        return submitRunnable(r,-1,-1);
    }

    template <typename T>
    sp<_Future> schedule(long delay,sp<T> r) {
        //r->setDelay(delay);
        return submitRunnable(r,delay,-1);
    }

    template<typename T>
    sp<_Future> preempt(int priority,sp<T> r) {
        //r->setPriority(priority);
        return submitRunnable(r,-1,priority);
    }

    template <class Function, class... Args>
    sp<_Future> submit(Function && f, Args && ... args) {
        return submitRunnable(Cast<Runnable>(createLambdaRunnable(f, args...)),-1,-1);
    }

    template <class Function, class... Args>
    sp<_Future> schedule(long delay,Function && f, Args && ... args) {
        Runnable r = createLambdaRunnable(f, args...);
        //r->setDelay(delay);
        return submitRunnable(r,delay,-1);
    }

    template <class Function, class... Args>
    sp<_Future> preempt(int priority,Function && f, Args && ... args) {
        Runnable r = createLambdaRunnable(f, args...);
        //r->setPriority(priority);
        return submitRunnable(r,-1,priority);
    }

    int getMaxPendingTaskNum();
    int getDefaultThreadNum();
    int getMaxThreadNum();
    int getMinThreadNum();
    uint32_t getMaxNoWorkingTime();
    uint32_t getMaxSubmitTaskWaitTime();

    virtual int getPendingTaskNum() = 0;
    virtual int getExecutingThreadNum() = 0;

    static sp<_ExecutorTask> getCurrentTask();
    static void setCurrentTask(sp<_ExecutorTask>);
    static void removeCurrentTask();

protected:
    void updateStatus(int);
    sp<_Future> submitRunnable(Runnable r,int delay,int priority);
    virtual sp<_Future> submitTask(sp<_ExecutorTask> task) = 0;

    int mMaxPendingTaskNum;
    int mDefaultThreadNum;
    int mMaxThreadNum;
    int mMinThreadNum;
    uint32_t mMaxNoWorkingTime;
    uint32_t mMaxSubmitTaskWaitTime;

private:
    AtomicInteger mStatus;
    static ThreadLocal<sp<_ExecutorTask>> ExecutorTasks;
};

} // namespace obotcha
#endif