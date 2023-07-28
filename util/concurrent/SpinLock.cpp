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

#include "SpinLock.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {

_SpinLock::_SpinLock(String n) : _SpinLock() { 
    mSpinLockName = n; 
}

_SpinLock::_SpinLock(const char *n) : _SpinLock(createString(n)) {
}

_SpinLock::_SpinLock() { 
    pthread_spin_init(&mLock, PTHREAD_PROCESS_PRIVATE); 
}

int _SpinLock::lock(long interval) {
    Panic(interval != 0,MethodNotSupportException,"interval must be 0")
    return -pthread_spin_lock(&mLock);
}

int _SpinLock::tryLock() {
    return -pthread_spin_trylock(&mLock);
}

int _SpinLock::unlock() {
    return -pthread_spin_unlock(&mLock);
}

_SpinLock::~_SpinLock() { 
    pthread_spin_destroy(&mLock); 
}

String _SpinLock::toString() { 
    return mSpinLockName; 
}

} // namespace obotcha
