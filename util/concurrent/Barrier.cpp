#include "Barrier.hpp"
#include "AutoLock.hpp"

namespace obotcha {

_Barrier::_Barrier(int n) {
    mBarrierNums = n;
    mBarrierBack = n;

    mutex = createMutex("BarrierMutex");
    cond = createCondition();
}

int _Barrier::await(long v) {
    AutoLock l(mutex);
    mBarrierNums--;
    if(mBarrierNums == 0) {
        cond->notifyAll();
        mBarrierNums = mBarrierBack;
    } else {
        return cond->wait(mutex,v);
    }

    return  0;
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