#include "Barrier.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"

namespace obotcha {

_Barrier::_Barrier(int n):mBarrierNums(n) {
}

int _Barrier::await(const std::function<void()> &func,long interval) {
    int result = 0;
    
    mMutex->lock();
    if(mBarrierNums == 0) {
        mMutex->unlock();
        return -1;
    }
    
    mBarrierNums--;
    if(mBarrierNums == 0) {
        mCond->notifyAll();
    } else if(mBarrierNums > 0) {
        result = mCond->wait(mMutex, interval);
    }

    mMutex->unlock();
    if(mBarrierNums == 0 && func != nullptr) {
        func();
    }
    
    return result;
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
