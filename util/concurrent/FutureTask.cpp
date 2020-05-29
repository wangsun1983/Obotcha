#include "FutureTask.hpp"
#include "AutoLock.hpp"
#include "Future.hpp"

namespace obotcha {

//remove soon
_FutureTask::_FutureTask(int type,Runnable r) {
    this->mType = type;
    this->mRunnable = r;

    mCompleteMutex = createMutex("FutureTaskMutex");
    mCompleteCond = createCondition();

    mStatus = st(Future)::Waiting;
}

_FutureTask::_FutureTask(int type,Runnable r,FutureTaskStatusListener l) {
    this->mType = type;
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
    AutoLock l(mCompleteMutex);
    if(mStatus == st(Future)::Complete || mStatus == st(Future)::Cancel) {
        return;
    }

    mCompleteCond->wait(mCompleteMutex);
}
    
int _FutureTask::wait(long interval) {
    AutoLock l(mCompleteMutex);
    
    if(mStatus == st(Future)::Complete || mStatus == st(Future)::Cancel) {
        return 0;
    }

    return mCompleteCond->wait(mCompleteMutex,interval);
}

void _FutureTask::cancel() {
    if(mStatus == st(Future)::Cancel) {
        return;
    }

    AutoLock l(mCompleteMutex);
    
    if(mStatus == st(Future)::Cancel) {
        return;
    }
    
    mStatus = st(Future)::Cancel;
    if(mRunnable != nullptr) {
        mRunnable->onInterrupt();
    }

    mCompleteCond->notify();

    if(mListener != nullptr) {
        FutureTask task;
        task.set_pointer(this);
        mListener->onCancel(task);
        mListener = nullptr;
        task = nullptr;
    }
    mRunnable = nullptr;
}

void _FutureTask::cancelWithoutCallback() {
    if(mStatus == st(Future)::Cancel) {
        return;
    }

    AutoLock l(mCompleteMutex);
    
    if(mStatus == st(Future)::Cancel) {
        return;
    }
    
    mStatus = st(Future)::Cancel;
    if(mRunnable != nullptr) {
        mRunnable->onInterrupt();
    }

    mCompleteCond->notify();
    mRunnable = nullptr;
}

int _FutureTask::getStatus() {
    return mStatus;
}

int _FutureTask::getType() {
    return mType;
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
