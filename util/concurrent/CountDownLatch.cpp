#include "CountDownLatch.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_CountDownLatch::_CountDownLatch(int count) {
    Panic(count <= 0,InitializeException, "count down latch is illegal");
    mCount = count;
    mWaitMutex = createMutex();
    mWaitCond = createCondition();
}

int _CountDownLatch::countDown() {
    AutoLock l(mWaitMutex);
    mCount--;
    if (mCount == 0) {
        mWaitCond->notifyAll();
    }

    return (mCount >= 0)?0:-1;
}

int _CountDownLatch::getCount() {
    AutoLock l(mWaitMutex);
    return mCount;
}

int _CountDownLatch::await(long interval) {
    AutoLock l(mWaitMutex);
    return (mCount > 0)? mWaitCond->wait(mWaitMutex, interval):-1;
}

int _CountDownLatch::release() {
    AutoLock l(mWaitMutex);
    if(mCount > 0) {
        mCount = 0;
        mWaitCond->notifyAll();
    }
    return 0;
}

} // namespace obotcha
