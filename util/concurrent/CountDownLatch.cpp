#include "CountDownLatch.hpp"
#include "Error.hpp"
#include "Thread.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_CountDownLatch::_CountDownLatch(int v) {
    if(v <= 0) {
        throwInitializeException("count down latch is illegal");
    }

    count = v;
    waitMutex = createMutex("CountDownLatchWaitMutex");
    waitCond = createCondition();
}

int _CountDownLatch::countDown() {
    AutoLock l(waitMutex);

    if(count == 0) {
        return -AlreadyDestroy;
    }

    count--;

    if(count == 0) {
        waitCond->notifyAll();
    }

    return 0;
}

int _CountDownLatch::await(long v) {
    AutoLock l(waitMutex);
    if(count == 0) {
        return -AlreadyDestroy;
    }
    
    return waitCond->wait(waitMutex,v);
}

int _CountDownLatch::await() {
    return await(0);
}

}
