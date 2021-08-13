#ifndef __OBOTCHA_EXECUTOR_TASK_HPP__
#define __OBOTCHA_EXECUTOR_TASK_HPP__

#include "Mutex.hpp"
#include "Condition.hpp"
#include "Runnable.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ExecutorTask) {
public:
    _ExecutorTask(Runnable);

    ~_ExecutorTask();

    int wait(long interval = 0);

    void cancel();

    int getStatus();

    void execute();

    Runnable getRunnable();
    
    template<typename T>
    T getResult(int interval = 0) {
        this->wait(interval);
        {
            AutoLock l(mMutex);
            if(mStatus != Complete) {
                Trigger(InterruptedException,"wait exception");
            }
        }
        return mRunnable->getResult<T>();
    }

    enum Status {
        Waiting = 0,
        Running,
        Cancel,
        Complete,
    };

private:

    Runnable mRunnable;

    int mStatus;

    Mutex mMutex;

    Condition mCompleteCond;
};

}
#endif