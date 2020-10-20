/**
 * @file SpinLock.cpp
 * @brief  a spinlock is a lock which causes a thread trying to 
 *         acquire it to simply wait in a loop ("spin") while 
 *         repeatedly checking if the lock is available
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "String.hpp"
#include "SpinLock.hpp"

namespace obotcha {

_SpinLock::_SpinLock(String n) {
    mSpinLockName = n;
}

_SpinLock::_SpinLock(const char *n) {
    mSpinLockName = createString(n);
}

_SpinLock::_SpinLock() {

}

int _SpinLock::lock() {
    while(mflag.test_and_set(std::memory_order_acquire));
    return 0;
}

int _SpinLock::unlock() {
    mflag.clear(std::memory_order_release);
    return 0;
}

_SpinLock::~_SpinLock() {}

String _SpinLock::toString() {
    return mSpinLockName;
}



}
