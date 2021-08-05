#ifndef __OBOTCHA_EXECUTOR_TASK_HPP__
#define __OBOTCHA_EXECUTOR_TASK_HPP__

#include "Mutex.hpp"
#include "Condition.hpp"
#include "Runnable.hpp"

namespace obotcha {

class _PriorityTaskManager;

DECLARE_SIMPLE_CLASS(ExecutorTask) {
public:
    friend class _PriorityTaskManager;

    _ExecutorTask(Runnable);

    ~_ExecutorTask();

    int wait(long interval = 0);

    void cancel();

    int getStatus();

    void execute();

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

    Mutex mMutex;

    Condition mCompleteCond;
};

}
#endif