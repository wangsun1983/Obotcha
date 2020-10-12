#include "Barrier.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"

namespace obotcha {

_Barrier::_Barrier(int n) {
    mBarrierNums = n;

    mutex = createMutex("BarrierMutex");
    cond = createCondition();
}

int _Barrier::await(long v) {
    AutoLock l(mutex);
    if(mBarrierNums == 0) {
        return -InvalidStatus;
    }

    mBarrierNums--;
    if(mBarrierNums == 0) {
        cond->notifyAll();
    } else {
        return cond->wait(mutex,v);
    }

    return 0;
}

int _Barrier::await() {
    AutoLock l(mutex);
    if(mBarrierNums == 0) {
        return -InvalidStatus;
    }

    mBarrierNums--;
    if(mBarrierNums == 0) {
        cond->notifyAll();
    } else {
        cond->wait(mutex);
    }

    return 0;
}

int _Barrier::getWaitNums() {
    AutoLock l(mutex);
    return mBarrierNums;
} 

}