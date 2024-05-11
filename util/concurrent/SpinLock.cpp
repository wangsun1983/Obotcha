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
#include <unistd.h>
#include <sys/syscall.h>

#include "SpinLock.hpp"
#include "MethodNotSupportException.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

_SpinLock::_SpinLock(String n):mSpinLockName(n) { 
    pthread_spin_init(&mLock, PTHREAD_PROCESS_PRIVATE); 
}

_SpinLock::_SpinLock(const char *n) : _SpinLock(String::New(n)) {
}

_SpinLock::_SpinLock() { 
    pthread_spin_init(&mLock, PTHREAD_PROCESS_PRIVATE); 
}

int _SpinLock::lock(long interval) {
    if(interval == st(Concurrent)::kWaitForEver) {
        auto ret = -pthread_spin_lock(&mLock);
        if(ret == 0) {
            mOwner = syscall(SYS_gettid);
        }
        return ret;
    }

    for(;interval > 0;interval -= 10) {
        if(pthread_spin_trylock(&mLock) != 0) {
            usleep(10*1000);
            continue;
        }
        mOwner = syscall(SYS_gettid);
        break;
    }

    return (interval > 0)?0:-EBUSY;
}

int _SpinLock::tryLock() {
    auto ret = -pthread_spin_trylock(&mLock);
    if(ret == 0) {
        mOwner = syscall(SYS_gettid);
    }
    return ret;
}

int _SpinLock::unlock() {
    if(mOwner != syscall(SYS_gettid)) {
        Trigger(IllegalStateException,"spinlock wrong owner")
    }

    auto ret = -pthread_spin_unlock(&mLock);
    if(ret == 0) {
        mOwner = 0;
    }
    return ret;
}

_SpinLock::~_SpinLock() { 
    pthread_spin_destroy(&mLock); 
}

String _SpinLock::toString() { 
    return mSpinLockName; 
}

} // namespace obotcha
