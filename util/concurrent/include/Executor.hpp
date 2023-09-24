#ifndef __OBOTCHA_EXECUTOR_HPP__
#define __OBOTCHA_EXECUTOR_HPP__

#include "Object.hpp"
#include "Runnable.hpp"
#include "ThreadLocal.hpp"
#include "Concurrent.hpp"

namespace obotcha {
class _ExecutorTask;
class _Future;

DECLARE_CLASS(Executor) {
public:
    _Executor();
    
    bool isExecuting();
    bool isShutDown();

    virtual int shutdown() = 0;
    virtual bool isTerminated() = 0;
    virtual int awaitTermination(long timeout = 0) = 0;

    template <typename T>
    sp<_Future> submit(sp<T> r) {
        return submitRunnable(r,0,st(Concurrent)::TaskPriority::Medium);
    }

    template <typename T>
    sp<_Future> schedule(long delay,sp<T> r) {
        return submitRunnable(r,delay,st(Concurrent)::TaskPriority::Medium);
    }

    template<typename T>
    sp<_Future> preempt(st(Concurrent)::TaskPriority priority,sp<T> r) {
        return submitRunnable(r,0,priority);
    }

    template <class Function, class... Args>
    sp<_Future> submit(Function f, Args... args) {
        return submitRunnable(Cast<Runnable>(createLambdaRunnable(f, args...)),
                                             0,
                                             st(Concurrent)::TaskPriority::Medium);
    }

    template <class Function, class... Args>
    sp<_Future> schedule(long delay,Function f, Args... args) {
        Runnable r = createLambdaRunnable(f, args...);
        return submitRunnable(r,delay,st(Concurrent)::TaskPriority::Medium);
    }

    template <class Function, class... Args>
    sp<_Future> preempt(st(Concurrent)::TaskPriority priority,Function f, Args... args) {
        Runnable r = createLambdaRunnable(f, args...);
        return submitRunnable(r,0,priority);
    }

    size_t getMaxPendingTaskNum() const;
    long getDefaultThreadNum() const;
    long getMaxThreadNum() const;
    long getMinThreadNum() const;
    uint32_t getMaxNoWorkingTime() const;
    uint32_t getMaxSubmitTaskWaitTime() const;

    virtual size_t getPendingTaskNum() = 0;
    virtual size_t getExecutingThreadNum() = 0;

    static sp<_ExecutorTask> GetCurrentTask();
    static void SetCurrentTask(sp<_ExecutorTask>);
    static void RemoveCurrentTask();

protected:
    void updateStatus(st(Concurrent)::Status);
    sp<_Future> submitRunnable(Runnable r,long delay,st(Concurrent)::TaskPriority priority);
    virtual sp<_Future> submitTask(sp<_ExecutorTask> task) = 0;
    virtual void onRemoveTask(sp<_ExecutorTask> task) = 0;

    size_t mMaxPendingTaskNum = 0;
    long mDefaultThreadNum = 0;
    long mMaxThreadNum = 0;
    long mMinThreadNum = 0;
    uint32_t mMaxNoWorkingTime = 0;
    uint32_t mMaxSubmitTaskWaitTime =0;

private:
    std::atomic<st(Concurrent)::Status> mStatus;
    static ThreadLocal<sp<_ExecutorTask>> ExecutorTasks;
};

} // namespace obotcha
#endif