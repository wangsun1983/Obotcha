#ifndef __OBOTCHA_EXECUTOR_TASK_HPP__
#define __OBOTCHA_EXECUTOR_TASK_HPP__

#include "AutoLock.hpp"
#include "Condition.hpp"
#include "Error.hpp"
#include "InterruptedException.hpp"
#include "Mutex.hpp"
#include "NullPointerException.hpp"
#include "OStdInstanceOf.hpp"
#include "Runnable.hpp"
#include "TimeOutException.hpp"


namespace obotcha {
class _ExecutorResult;
class _Future;

DECLARE_CLASS(ExecutorTask) {
public:
    friend class _ExecutorResult;
    friend class _Future;
    
    _ExecutorTask(Runnable);

    ~_ExecutorTask();

    int wait(long interval = 0);

    void cancel();

    int getStatus();

    void setPending();

    void execute();

    Runnable getRunnable();

    enum Status {
        Waiting = 0,
        Pending,
        Running,
        Cancel,
        Complete,
    };

private:
    Runnable mRunnable;

    int mStatus;

    Mutex mMutex;

    Condition mCompleteCond;

    //Object mResult;
    sp<_ExecutorResult> mResult;
};

} // namespace obotcha
#endif