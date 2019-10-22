#include "FutureTask.hpp"
#include "AutoMutex.hpp"
#include "Future.hpp"

namespace obotcha {

//remove soon
_FutureTask::_FutureTask(int type,Runnable r) {
    this->mType = type;
    this->mRunnable = r;

    mCompleteMutex = createMutex("FutureTaskMutex");
    mCompleteCond = createCondition();

    mStatus = FUTURE_WAITING;
}

_FutureTask::_FutureTask(int type,Runnable r,FutureTaskStatusListener l) {
    this->mType = type;
    this->mRunnable = r;
    this->mListener = l;

    mCompleteMutex = createMutex("FutureTaskMutex");
    mCompleteCond = createCondition();

    mStatus = FUTURE_WAITING;
}

_FutureTask::~_FutureTask() {
    this->mRunnable = nullptr;
    this->mListener = nullptr;
}

void _FutureTask::wait() {
    AutoMutex l(mCompleteMutex);
    if(mStatus == FUTURE_COMPLETE || mStatus == FUTURE_CANCEL) {
        return;
    }

    mCompleteCond->wait(mCompleteMutex);
}
    
void _FutureTask::wait(long interval) {
    AutoMutex l(mCompleteMutex);
    
    if(mStatus == FUTURE_COMPLETE || mStatus == FUTURE_CANCEL) {
        return;
    }

    mCompleteCond->wait(mCompleteMutex,interval);
}

void _FutureTask::cancel() {
    if(mStatus == FUTURE_CANCEL) {
        return;
    }

    AutoMutex l(mCompleteMutex);
    
    if(mStatus == FUTURE_CANCEL) {
        return;
    }

    mStatus = FUTURE_CANCEL;
    if(mRunnable != nullptr) {
        mRunnable->onInterrupt();
    }

    mRunnable = nullptr;
    mCompleteCond->notify();

    if(mListener != nullptr) {
        FutureTask task;
        task.set_pointer(this);
        mListener->onCancel(task);
        mListener = nullptr;
        task = nullptr;
    }
}

int _FutureTask::getStatus() {
    return mStatus;
}

int _FutureTask::getType() {
    return mType;
}

void _FutureTask::onRunning() {
    AutoMutex l(mCompleteMutex);
    mStatus = FUTURE_RUNNING;
}

void _FutureTask::onComplete() {
    AutoMutex l(mCompleteMutex);
    mCompleteCond->notify();
    mStatus = FUTURE_COMPLETE;
}

Runnable _FutureTask::getRunnable() {
    AutoMutex l(mCompleteMutex);
    return mRunnable;
}

}
