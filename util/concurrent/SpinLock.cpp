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
    pthread_spin_init(&mLock, 0);
}

_SpinLock::_SpinLock(const char *n) {
    mSpinLockName = createString(n);
    pthread_spin_init(&mLock, 0);
}

_SpinLock::_SpinLock() {
    pthread_spin_init(&mLock, 0);
}

int _SpinLock::lock() {
    pthread_spin_lock(&mLock);
    return 0;
}

int _SpinLock::unlock() {
    pthread_spin_unlock(&mLock);
    return 0;
}

_SpinLock::~_SpinLock() {
    pthread_spin_destroy(&mLock);
}

String _SpinLock::toString() {
    return mSpinLockName;
}



}
