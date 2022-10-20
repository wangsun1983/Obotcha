#include "Executor.hpp"
#include "AutoLock.hpp"

namespace obotcha {

_Executor::_Executor() {
    //mMutex = createMutex();
    mStatus = createAtomicInteger(Idle);
    mQueueTimeout = 0;
}

bool _Executor::isExecuting() {
    //AutoLock l(mMutex);
    return mStatus->get() == Executing;
}

bool _Executor::isShutDown() {
    //AutoLock l(mMutex);
    return mStatus->get() == ShutDown;
}

void _Executor::updateStatus(int s) {
    //AutoLock l(mMutex);
    //mStatus = s;
    mStatus->set(s);
}

void _Executor::setQueueTimeout(long l) {
    mQueueTimeout = l;
}

long _Executor::getQueueTimeout() {
    return mQueueTimeout;
}

} // namespace obotcha