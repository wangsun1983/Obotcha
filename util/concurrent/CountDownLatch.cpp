#include "CountDownLatch.hpp"
#include "Error.hpp"
#include "Thread.hpp"

namespace obotcha {

_CountDownLatch::_CountDownLatch(int v) {
    count = v;
    waitMutex = createMutex("CountDownLatchWaitMutex");
    waitCond = createCondition();
}

int _CountDownLatch::countDown() {
    AutoLock l(waitMutex);

    if(count < 1) {
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
    AutoLock l(waitMutex);
    if(count == 0) {
        return -AlreadyDestroy;
    }
    
    waitCond->wait(waitMutex);

    return 0;
}

}
