/**
 * @file ExecutorTask.cpp
 * @brief A cancellable asynchronous computation.  This class provides a base implementation of Future
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

namespace obotcha {

_ExecutorTask::_ExecutorTask(Runnable r) {
    this->mRunnable = r;

    mMutex = createMutex("ExecutorTaskMutex");
    mCompleteCond = createCondition();

    mStatus = Waiting;
}

_ExecutorTask::~_ExecutorTask() {
    this->mRunnable = nullptr;
}
    
int _ExecutorTask::wait(long interval) {
    AutoLock l(mMutex);
    
    if(mStatus == Complete || mStatus == Cancel) {
        return 0;
    }

    return mCompleteCond->wait(mMutex,interval);
}

void _ExecutorTask::cancel() {
    AutoLock l(mMutex);
    if(mStatus == Cancel || mStatus == Complete) {
        return;
    }
    
    mStatus = Cancel;
    if(mRunnable != nullptr) {
        mRunnable->onInterrupt();
    }

    mCompleteCond->notify();
    mRunnable = nullptr;
}

int _ExecutorTask::getStatus() {
    AutoLock l(mMutex);
    return mStatus;
}

void _ExecutorTask::execute() {
    {
        AutoLock l(mMutex);
        if(mStatus == Complete || mStatus == Cancel) {
            return;
        }

        mStatus = Running;
    }

    if(mRunnable != nullptr) {
        mRunnable->run();
    }

    {
        AutoLock l(mMutex);
        mStatus = Complete;
        mCompleteCond->notify();
    }
}

Runnable _ExecutorTask::getRunnable() {
    return mRunnable;
}

}
