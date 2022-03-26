#include "CountDownLatch.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "Thread.hpp"

namespace obotcha {

_CountDownLatch::_CountDownLatch(int v) {
    if (v <= 0) {
        Trigger(InitializeException, "count down latch is illegal");
    }

    count = v;
    waitMutex = createMutex();
    waitCond = createCondition();
}

int _CountDownLatch::countDown() {
    AutoLock l(waitMutex);
    
    if (count == 0) {
        return -AlreadyDestroy;
    }

    count--;

    if (count == 0) {
        waitCond->notifyAll();
    }

    return SUCCESS;
}

int _CountDownLatch::getCount() {
    AutoLock l(waitMutex);
    return count;
}

int _CountDownLatch::await(long v) {
    AutoLock l(waitMutex);
    return (count == 0)? -AlreadyDestroy:waitCond->wait(waitMutex, v);
}

int _CountDownLatch::release() {
    AutoLock l(waitMutex);
    if(count != 0) {
        count = 0;
        waitCond->notifyAll();
    }

    return 0;
}

} // namespace obotcha
