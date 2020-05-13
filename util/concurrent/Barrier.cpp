#include "Barrier.hpp"
#include "AutoLock.hpp"

namespace obotcha {

_Barrier::_Barrier(int n) {
    mBarrierNums = n;
    mBarrierBack = n;

    mutex = createMutex("BarrierMutex");
    cond = createCondition();
}

void _Barrier::await(long v) {
    AutoLock l(mutex);
    mBarrierNums--;
    if(mBarrierNums == 0) {
        cond->notifyAll();
        mBarrierNums = mBarrierBack;
    } else {
        cond->wait(mutex,v);
    }
}

void _Barrier::await() {
    AutoLock l(mutex);
    mBarrierNums--;
    if(mBarrierNums == 0) {
        cond->notifyAll();
        mBarrierNums = mBarrierBack;
    } else {
        cond->wait(mutex);
    }
}

int _Barrier::getWaitNums() {
    AutoLock l(mutex);
    return mBarrierBack - mBarrierNums;
} 

}