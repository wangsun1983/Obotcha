#include "Executor.hpp"
#include "AutoLock.hpp"

namespace obotcha {

_Executor::_Executor() {
    mMutex = createMutex();
    mStatus = Idle;
    mQueueTimeout = 0;
}

bool _Executor::isExecuting() {
    AutoLock l(mMutex);
    return mStatus == Executing;
}

bool _Executor::isShutDown() {
    AutoLock l(mMutex);
    return mStatus == ShutDown;
}

void _Executor::updateStatus(int s) {
    AutoLock l(mMutex);
    mStatus = s;
}

void _Executor::setQueueTimeout(long l) {
    mQueueTimeout = l;
}

long _Executor::getQueueTimeout() {
    return mQueueTimeout;
}

} // namespace obotcha