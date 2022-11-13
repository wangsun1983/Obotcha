/**
 * @file ExecutorTask.cpp
 * @brief Executor process uinit
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#ifndef __OBOTCHA_EXECUTOR_TASK_HPP__
#define __OBOTCHA_EXECUTOR_TASK_HPP__

#include "Object.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"
#include "Runnable.hpp"

namespace obotcha {
class _ExecutorResult;
class _Future;

DECLARE_CLASS(ExecutorTask) {
public:
    friend class _ExecutorResult;
    friend class _Future;
    
    _ExecutorTask(Runnable);

    _ExecutorTask(Runnable,int delay,int priority);

    ~_ExecutorTask();

    int wait(long interval = 0);

    void cancel();

    int getStatus();

    void setPending();

    void execute();

    //Priority
    void setPriority(int);
    int getPriority();

    //Delay
    void setDelay(int);
    int getDelay();

    Runnable getRunnable();

    enum Status {
        Idle = 0,
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

    int mDelay;

    int mPriority;

    //Object mResult;
    sp<_ExecutorResult> mResult;
};

} // namespace obotcha
#endif