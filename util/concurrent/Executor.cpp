#include "Executor.hpp"
#include "AutoLock.hpp"

namespace obotcha {

_Executor::_Executor() {
    mStatus = createAtomicInteger(Idle);
    //mQueueTimeout = 0;
}

bool _Executor::isExecuting() {
    return mStatus->get() == Executing;
}

bool _Executor::isShutDown() {
    return mStatus->get() == ShutDown;
}

void _Executor::updateStatus(int s) {
    mStatus->set(s);
}

//void _Executor::setQueueTimeout(long l) {
    //mQueueTimeout = l;
//}

//long _Executor::getQueueTimeout() {
//    return mQueueTimeout;
//}

} // namespace obotcha