/**
 * @file FutureTask.cpp
 * @brief A cancellable asynchronous computation.  This class provides a base implementation of Future
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "FutureTask.hpp"
#include "AutoLock.hpp"
#include "Future.hpp"

namespace obotcha {

_FutureTask::_FutureTask(Runnable r):_FutureTask(r,nullptr) {
}

_FutureTask::_FutureTask(Runnable r,FutureTaskStatusListener l) {
    this->mRunnable = r;
    this->mListener = l;

    mCompleteMutex = createMutex("FutureTaskMutex");
    mCompleteCond = createCondition();

    mStatus = st(Future)::Waiting;
}

_FutureTask::~_FutureTask() {
    this->mRunnable = nullptr;
    this->mListener = nullptr;
}

void _FutureTask::wait() {
    wait(0);
}
    
int _FutureTask::wait(long interval) {
    AutoLock l(mCompleteMutex);
    
    if(mStatus == st(Future)::Complete || mStatus == st(Future)::Cancel) {
        return 0;
    }

    return mCompleteCond->wait(mCompleteMutex,interval);
}

void _FutureTask::cancel() {
    AutoLock l(mCompleteMutex);
    printf("cancel trace1 \n");
    onShutDown();

    if(mListener != nullptr) {
        mListener->onCancel(AutoClone(this));
        mListener = nullptr;
    }
    mRunnable = nullptr;
}

void _FutureTask::onShutDown() {
    AutoLock l(mCompleteMutex);
    
    if(mStatus == st(Future)::Cancel || mStatus == st(Future)::Complete) {
        return;
    }
    
    mStatus = st(Future)::Cancel;
    if(mRunnable != nullptr) {
        printf("onInterrupt trace1 \n");
        mRunnable->onInterrupt();
        mRunnable->interruptResultWait();
    }

    mCompleteCond->notify();
}

int _FutureTask::getStatus() {
    AutoLock l(mCompleteMutex);
    return mStatus;
}

void _FutureTask::onRunning() {
    AutoLock l(mCompleteMutex);
    mStatus = st(Future)::Running;
}

void _FutureTask::onComplete() {
    AutoLock l(mCompleteMutex);
    mCompleteCond->notify();
    mStatus = st(Future)::Complete;
}

Runnable _FutureTask::getRunnable() {
    AutoLock l(mCompleteMutex);
    return mRunnable;
}

}
