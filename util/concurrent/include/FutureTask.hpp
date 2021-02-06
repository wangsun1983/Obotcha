#ifndef __OBOTCHA_FUTURE_TASK_HPP__
#define __OBOTCHA_FUTURE_TASK_HPP__

#include "Mutex.hpp"
#include "Condition.hpp"
#include "Runnable.hpp"

namespace obotcha {

class _FutureTask;
class _PriorityTaskManager;

DECLARE_SIMPLE_CLASS(FutureTask) {
public:
    friend class _PriorityTaskManager;

    _FutureTask(Runnable);

    ~_FutureTask();

    void wait();

    int wait(long);

    void cancel();

    int getStatus();

    virtual void onComplete();

    void onRunning();

    Runnable getRunnable();

    template<typename T>
    T getResult(T defaultvalue,long millseconds = 0) {
        T v;
        mRunnable->getResult(v,defaultvalue,millseconds);
        return v;
    }

private:

    Runnable mRunnable;

    int mStatus;

    Mutex mCompleteMutex;

    Condition mCompleteCond;
};

}
#endif