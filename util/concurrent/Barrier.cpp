#include "Barrier.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"

namespace obotcha {

_Barrier::_Barrier(int n) {
    mBarrierNums = n;
    mMutex = createMutex();
    mCond = createCondition();
}

int _Barrier::await(long interval) {
    return await(nullptr,interval);
}

int _Barrier::getWaitNums() {
    AutoLock l(mMutex);
    return mBarrierNums;
}

int _Barrier::release() {
    AutoLock l(mMutex);
    if(mBarrierNums != 0) {
        mBarrierNums = 0;
        mCond->notifyAll();
    }
    return 0;
}

} // namespace obotcha
