#include "CountDownLatch.hpp"

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
        return -1;
    }

    count--;

    if(count == 0) {
        waitCond->notify();
    }

    return 0;
}

void _CountDownLatch::await(long v) {
    AutoMutex l(waitMutex);
    if(count == 0) {
        return;
    }
    
    waitCond->wait(waitMutex,v);
}

}
