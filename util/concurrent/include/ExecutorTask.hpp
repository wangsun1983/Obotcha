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
#include "Concurrent.hpp"

namespace obotcha {
class _ExecutorResult;
class _ExecutorTask;
class _Future;

using RemoveFunction = std::function<void(sp<_ExecutorTask>)>;

DECLARE_CLASS(ExecutorTask) {
public:
    friend class _ExecutorResult;
    friend class _Future;
    
    _ExecutorTask(Runnable,RemoveFunction);

    _ExecutorTask(Runnable,RemoveFunction,long delay,st(Concurrent)::TaskPriority priority);

    ~_ExecutorTask() override;

    int wait(long interval = 0);

    void cancel();

    st(Concurrent)::Status getStatus();

    void setPending();

    void execute();

    //Priority
    void setPriority(st(Concurrent)::TaskPriority);
    st(Concurrent)::TaskPriority getPriority() const;

    //Delay
    void setDelay(long);
    long getDelay() const;

    Runnable getRunnable();

private:
    Runnable mRunnable;

    st(Concurrent)::Status mStatus = st(Concurrent)::Status::Idle;

    Mutex mMutex = createMutex("ExecutorTaskMutex");

    Condition mCompleteCond = createCondition();

    long mDelay;

    st(Concurrent)::TaskPriority mPriority = st(Concurrent)::TaskPriority::Medium;

    sp<_ExecutorResult> mResult;

    RemoveFunction mRemoveFunction;
};

} // namespace obotcha
#endif