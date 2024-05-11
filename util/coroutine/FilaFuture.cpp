#include "FilaFuture.hpp"

namespace obotcha {

void _FilaFuture::setOwner(stCoRoutine_t *co) {
    this->owner = co;
}

st(Concurrent)::Status _FilaFuture::getStatus() const {
    return mStatus;
}

void _FilaFuture::setStatus(st(Concurrent)::Status type) {
    mStatus = type;
}

FilaExecutorResult _FilaFuture::genResult() {
    mResult = FilaExecutorResult::New();
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
