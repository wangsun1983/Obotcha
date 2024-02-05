/**
 * @file Barrier.cpp
 * @brief  A synchronization aid that allows a set of threads to all wait 
 * for each other to reach a common barrier point. Barrier are useful in 
 * programs involving a fixed sized party of threads that must occasionally 
 * wait for each other. 
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-15
 * @license none
 */

#include "Barrier.hpp"
#include "AutoLock.hpp"
#include "Inspect.hpp"

namespace obotcha {

_Barrier::_Barrier(int n):mBarrierNums(n) {
}

int _Barrier::await(const std::function<void()> &func,long interval) {
    int result = 0;
    
    {
        AutoLock l(mMutex);
        Inspect(mBarrierNums == 0,-1)
        
        mBarrierNums--;
        if(mBarrierNums == 0) {
            mCond->notifyAll();
        } else if(mBarrierNums > 0) {
            result = mCond->wait(mMutex, interval);
        }
    }

    if(result == 0 && func != nullptr) {
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
