/**
 * @file Barrier.cpp
 * @brief barrier wait
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Barrier.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

_Barrier::_Barrier(int n) {
    mBarrierNums = n;
    mutex = createMutex();
    cond = createCondition();
}

int _Barrier::await(long interval) {
    return await(nullptr,interval);
}

int _Barrier::getWaitNums() {
    AutoLock l(mutex);
    return mBarrierNums;
}

int _Barrier::release() {
    AutoLock l(mutex);
    if(mBarrierNums != 0) {
        mBarrierNums = 0;
        cond->notifyAll();
    }
    return 0;
}

} // namespace obotcha
