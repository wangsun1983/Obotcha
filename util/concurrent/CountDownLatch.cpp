#include "CountDownLatch.hpp"
#include "Error.hpp"
#include "Thread.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_CountDownLatch::_CountDownLatch(int v) {
    if(v <= 0) {
        Trigger(InitializeException,"count down latch is illegal");
    }

    count = v;
    waitMutex = createMutex();
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

int _CountDownLatch::getCount() {
    AutoLock l(waitMutex);
    return count;
}

int _CountDownLatch::await(long v) {
    AutoLock l(waitMutex);
    if(count == 0) {
        return -AlreadyDestroy;
    }
    
    return waitCond->wait(waitMutex,v);
}

}
