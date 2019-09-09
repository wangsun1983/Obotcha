#include "CountDownLatch.hpp"
#include "Error.hpp"

namespace obotcha {

_CountDownLatch::_CountDownLatch(int v) {
    count = v;
    mutex = createMutex("CountDownLoatchMutex");
    waitMutex = createMutex("CountDownLatchWaitMutex");
    waitCond = createCondition();
}

int _CountDownLatch::countDown() {
    AutoMutex l(mutex);

    if(count < 1) {
        return -AlreadyDestroy;
    }

    count--;

    if(count == 0) {
        waitCond->notify();
    }

    return 0;
}

int _CountDownLatch::await(long v) {
    AutoMutex l(waitMutex);
    if(count == 0) {
        return -AlreadyDestroy;
    }
    
    if(NotifyByTimeout == waitCond->wait(waitMutex,v)) {
        return -WaitTimeout;
    }

    return 0;
}

int _CountDownLatch::await() {
    AutoMutex l(waitMutex);
    if(count == 0) {
        return -AlreadyDestroy;
    }
    
    waitCond->wait(waitMutex);

    return 0;
}

}
