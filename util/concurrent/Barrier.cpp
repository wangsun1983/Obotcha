#include "Barrier.hpp"
#include "AutoMutex.hpp"

namespace obotcha {

_Barrier::_Barrier(int n) {
    mBarrierNums = n;
    mBarrierBack = n;

    mutex = createMutex();
    cond = createCondition();
}

void _Barrier::await(long v) {
    AutoMutex l(mutex);
    mBarrierNums--;
    if(mBarrierNums == 0) {
        cond->notifyAll();
        mBarrierNums = mBarrierBack;
    } else {
        cond->wait(mutex,v);
    }
}

void _Barrier::await() {
    AutoMutex l(mutex);
    mBarrierNums--;
    if(mBarrierNums == 0) {
        cond->notifyAll();
        mBarrierNums = mBarrierBack;
    } else {
        cond->wait(mutex);
    }
}

int _Barrier::getWaitNums() {
    AutoMutex l(mutex);
    return mBarrierBack - mBarrierNums;
} 

}