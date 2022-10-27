/**
 * @file ExecutorTask.cpp
 * @brief A cancellable asynchronous computation.  This class provides a base
 * implementation of Future
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "ExecutorTask.hpp"
#include "AutoLock.hpp"
#include "ExecutorResult.hpp"

namespace obotcha {

_ExecutorTask::_ExecutorTask(Runnable r) {
    this->mRunnable = r;
    mMutex = createMutex("ExecutorTaskMutex");
    mCompleteCond = createCondition();
    mStatus = Waiting;
    mResult = createExecutorResult();
}

_ExecutorTask::~_ExecutorTask() { 
    this->mRunnable = nullptr; 
}

int _ExecutorTask::wait(long interval) {
    AutoLock l(mMutex);
    if (mStatus == Complete || mStatus == Cancel) {
        return -1;
    }
    return mCompleteCond->wait(mMutex, interval);
}

void _ExecutorTask::cancel() {
    AutoLock l(mMutex);
    if (mStatus == Cancel || mStatus == Complete) {
        return;
    }
    
    if (mRunnable != nullptr) {
        bool ret = mRunnable->onInterrupt();
        if(!ret && mStatus == Running) {
            return;
        }
    }
    
    mStatus = Cancel;

    mCompleteCond->notify();
    mRunnable = nullptr;
}

int _ExecutorTask::getStatus() {
    AutoLock l(mMutex);
    return mStatus;
}

void _ExecutorTask::setPending() {
    AutoLock l(mMutex);
    mStatus = Pending;
}

void _ExecutorTask::execute() {
    Runnable r = nullptr;

    {
        AutoLock l(mMutex);
        if (mStatus == Complete || mStatus == Cancel) {
            return;
        }

        mStatus = Running;
        r = mRunnable;
    }

    st(Executor)::setCurrentTask(AutoClone(this));
    
    if (r != nullptr) {
        r->run();
    }

    st(Executor)::removeCurrentTask();

    {
        AutoLock l(mMutex);
        mStatus = Complete;
        mCompleteCond->notify();
    }
}

Runnable _ExecutorTask::getRunnable() { 
    return mRunnable; 
}

} // namespace obotcha
