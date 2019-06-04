#include "FutureTask.hpp"
#include "AutoMutex.hpp"
#include "Future.hpp"

namespace obotcha {

_FutureTask::_FutureTask(int type,Runnable r) {
    this->mType = type;
    this->mRunnable = r;

    mCompleteMutex = createMutex("FutureTaskMutex");
    mCompleteCond = createCondition();

    mStatus = FUTURE_WAITING;
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
    AutoMutex l(mCompleteMutex);
    mRunnable = nullptr;
    mStatus = FUTURE_CANCEL;

    mCompleteCond->notify();
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
