#ifndef __FEATURE_TASK_HPP__
#define __FEATURE_TASK_HPP__

#include "Mutex.hpp"
#include "Condition.hpp"
#include "Runnable.hpp"

namespace obotcha {

class _FutureTask;

enum FutureTaskType {
    FUTURE_TASK_NORMAL,
    FUTURE_TASK_SUBMIT
};

DECLARE_SIMPLE_CLASS(FutureTaskStatusListener) {
public:    
    virtual void onCancel(sp<_FutureTask>) = 0;
};

DECLARE_SIMPLE_CLASS(FutureTask) {
public:
    _FutureTask(int,Runnable);//remove soon

    _FutureTask(int,Runnable,FutureTaskStatusListener);

    ~_FutureTask();

    void wait();

    int wait(long);

    void cancel();

    int getStatus();

    int getType();

    void onComplete();

    void onRunning();

    Runnable getRunnable();


private:
    Runnable mRunnable;

    int mType;

    int mStatus;

    Mutex mCompleteMutex;

    Condition mCompleteCond;

    FutureTaskStatusListener mListener; 
};

}
#endif