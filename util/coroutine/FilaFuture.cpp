#include "FilaFuture.hpp"

namespace obotcha {

_FilaFuture::_FilaFuture() {
    mMutex = createFilaMutex();
    mCond = createFilaCondition();
    mStatus = Idle;
}

void _FilaFuture::setOwner(stCoRoutine_t *owner) {
    this->owner = owner;
}

int _FilaFuture::getStatus() {
    return mStatus;
}

void _FilaFuture::setStatus(int type) {
    mStatus = type;
}

FilaExecutorResult _FilaFuture::genResult() {
    mResult = createFilaExecutorResult();
    return mResult;
}

void _FilaFuture::wake() {
    mCond->notify();
}

void _FilaFuture::wakeAll() {
    mCond->notifyAll();
}

int _FilaFuture::wait(long interval) {
    AutoLock l(mMutex);
    return mCond->wait(mMutex,interval);
}

} // namespace obotcha
