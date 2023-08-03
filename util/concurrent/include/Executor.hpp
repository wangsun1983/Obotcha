#ifndef __OBOTCHA_EXECUTOR_HPP__
#define __OBOTCHA_EXECUTOR_HPP__

#include "Object.hpp"
#include "Runnable.hpp"
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
        printf("Executor start submit \n");
        return submitRunnable(r,-1,Medium);
    }

    template <typename T>
    sp<_Future> schedule(long delay,sp<T> r) {
        return submitRunnable(r,delay,Medium);
    }

    template<typename T>
    sp<_Future> preempt(int priority,sp<T> r) {
        return submitRunnable(r,-1,priority);
    }

    template <class Function, class... Args>
    sp<_Future> submit(Function f, Args... args) {
        return submitRunnable(Cast<Runnable>(createLambdaRunnable(f, args...)),-1,-1);
    }

    template <class Function, class... Args>
    sp<_Future> schedule(long delay,Function f, Args... args) {
        Runnable r = createLambdaRunnable(f, args...);
        return submitRunnable(r,delay,Medium);
    }

    template <class Function, class... Args>
    sp<_Future> preempt(int priority,Function f, Args... args) {
        Runnable r = createLambdaRunnable(f, args...);
        return submitRunnable(r,-1,priority);
    }

    int getMaxPendingTaskNum() const;
    int getDefaultThreadNum() const;
    int getMaxThreadNum() const;
    int getMinThreadNum() const;
    uint32_t getMaxNoWorkingTime() const;
    uint32_t getMaxSubmitTaskWaitTime() const;

    virtual int getPendingTaskNum() = 0;
    virtual int getExecutingThreadNum() = 0;

    static sp<_ExecutorTask> getCurrentTask();
    static void setCurrentTask(sp<_ExecutorTask>);
    static void removeCurrentTask();

protected:
    void updateStatus(int);
    sp<_Future> submitRunnable(Runnable r,int delay,int priority);
    virtual sp<_Future> submitTask(sp<_ExecutorTask> task) = 0;
    virtual void onRemoveTask(sp<_ExecutorTask> task) = 0;

    int mMaxPendingTaskNum = 0;
    int mDefaultThreadNum = 0;
    int mMaxThreadNum = 0;
    int mMinThreadNum = 0;
    uint32_t mMaxNoWorkingTime = 0;
    uint32_t mMaxSubmitTaskWaitTime =0;

private:
    AtomicInteger mStatus;
    static ThreadLocal<sp<_ExecutorTask>> ExecutorTasks;
};

} // namespace obotcha
#endif