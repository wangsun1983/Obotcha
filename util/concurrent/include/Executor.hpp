#ifndef __OBOTCHA_EXECUTOR_HPP__
#define __OBOTCHA_EXECUTOR_HPP__

#include "Condition.hpp"
#include "InterruptedException.hpp"
#include "Mutex.hpp"
#include "OStdInstanceOf.hpp"
#include "Runnable.hpp"
#include "TimeOutException.hpp"
#include "Future.hpp"
#include "Mutex.hpp"
#include "AtomicInteger.hpp"

namespace obotcha {

DECLARE_CLASS(Executor) {
public:
    enum Status {
        Idle = 0,
        Executing,
        ShutDown,
    };

    enum Priority { Low = 0, Medium, High, NoUse };
    
    _Executor();
    bool isExecuting();
    bool isShutDown();

    virtual int shutdown() = 0;

    virtual bool isTerminated() = 0;

    virtual int awaitTermination(long timeout = 0) = 0;

    template <typename T>
    Future submit(sp<T> r) {
        return submitRunnable(r);
    }

    template <typename T>
    Future schedule(long delay,sp<T> r) {
        r->setDelay(delay);
        return submitRunnable(r);
    }

    template<typename T>
    Future preempt(int priority,sp<T> r) {
        r->setPriority(priority);
        return submitRunnable(r);
    }

    template <class Function, class... Args>
    Future submit(Function && f, Args && ... args) {
        return submitRunnable(Cast<Runnable>(createLambdaRunnable(f, args...)));
    }

    template <class Function, class... Args>
    Future schedule(long delay,Function && f, Args && ... args) {
        Runnable r = createLambdaRunnable(f, args...);
        r->setDelay(delay);
        return submitRunnable(r);
    }

    template <class Function, class... Args>
    Future preempt(int priority,Function && f, Args && ... args) {
        Runnable r = createLambdaRunnable(f, args...);
        r->setPriority(priority);
        return submitRunnable(r);
    }

    //void setQueueTimeout(long);
    //long getQueueTimeout();

protected:
    void updateStatus(int);
    virtual Future submitRunnable(Runnable r) = 0;
    virtual Future submitTask(ExecutorTask task) = 0;
    //long mQueueTimeout;

private:
    //Mutex mMutex;
    AtomicInteger mStatus;
    
};

} // namespace obotcha
#endif