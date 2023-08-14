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
class _ExecutorTask;
class _Future;

using RemoveFunction = std::function<void(sp<_ExecutorTask>)>;

DECLARE_CLASS(ExecutorTask) {
public:
    friend class _ExecutorResult;
    friend class _Future;

    enum class Status {
        Idle = 0,
        Pending,
        Running,
        Cancel,
        Complete,
    };
    
    _ExecutorTask(Runnable,RemoveFunction);

    _ExecutorTask(Runnable,RemoveFunction,long delay,int priority);

    ~_ExecutorTask() override;

    int wait(long interval = 0);

    void cancel();

    _ExecutorTask::Status getStatus();

    void setPending();

    void execute();

    //Priority
    void setPriority(int);
    int getPriority() const;

    //Delay
    void setDelay(long);
    long getDelay() const;

    Runnable getRunnable();

private:
    Runnable mRunnable;

    _ExecutorTask::Status mStatus = _ExecutorTask::Status::Idle;

    Mutex mMutex = createMutex("ExecutorTaskMutex");

    Condition mCompleteCond = createCondition();

    long mDelay;

    int mPriority = 0;

    sp<_ExecutorResult> mResult;

    RemoveFunction mRemoveFunction;
};

} // namespace obotcha
#endif