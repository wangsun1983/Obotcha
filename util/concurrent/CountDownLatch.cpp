/**
 * @file CountDownLatch.cpp
 * @brief  A synchronization aid that allows one or more threads to wait until
 * a set of operations being performed in other threads completes.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-15
 * @license none
 */

#include "CountDownLatch.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_CountDownLatch::_CountDownLatch(uint32_t count) {
    Panic(count == 0,InitializeException,"Invalid param")
    mCount = count;
}

int _CountDownLatch::countDown() {
    AutoLock l(mWaitMutex);
    Inspect(mCount == 0, -1);

    if (--mCount == 0) {
        mWaitCond->notifyAll();
    }

    return 0;
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
    Inspect(mCount == 0,0)

    mCount = 0;
    mWaitCond->notifyAll();
    return 0;
}

} // namespace obotcha
