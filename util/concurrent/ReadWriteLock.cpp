/**
 * @file ReadWriteLock.cpp
 * @brief  ReadWriteLock is a tool for read/write access to a shared resource by
 * multiple threads
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <pthread.h>

#include "Error.hpp"
#include "ReadWriteLock.hpp"
#include "StrongPointer.hpp"
#include "System.hpp"

namespace obotcha {

//------------ ReadLock ------------
_ReadLock::_ReadLock(sp<_ReadWriteLock> l, String s) {
    this->rwlock = l;
    mName = s;
}

int _ReadLock::lock() {
    int ret = pthread_rwlock_rdlock(&rwlock->rwlock);
    return 0;
}

int _ReadLock::unlock() {
    int ret = pthread_rwlock_unlock(&rwlock->rwlock);
    return ret;
}

int _ReadLock::tryLock() {
    int ret = pthread_rwlock_tryrdlock(&rwlock->rwlock);
    switch (ret) {
    case EBUSY:
        return -LockBusy;

    case SUCCESS:
        return SUCCESS;

    default:
        return -LockFail;
    }
}

String _ReadLock::getName() { return mName; }

int _ReadLock::lock(long timeInterval) {
    struct timespec ts;

    st(System)::getNextTime(timeInterval, &ts);
    if (pthread_rwlock_timedrdlock(&rwlock->rwlock, &ts) == ETIMEDOUT) {
        return -WaitTimeout;
    }

    return 0;
}

//------------ WriteLock ------------//
_WriteLock::_WriteLock(sp<_ReadWriteLock> l, String s) {
    rwlock = l;
    mName = s;
}

int _WriteLock::lock() {
    if(pthread_rwlock_wrlock(&rwlock->rwlock) != 0) {
        return -LockFail;
    }

    return 0;
}

int _WriteLock::unlock() {
    if(pthread_rwlock_unlock(&rwlock->rwlock) != 0) {
        return -LockFail;
    }

    return 0;
}

int _WriteLock::tryLock() {
    int ret = pthread_rwlock_trywrlock(&rwlock->rwlock);
    switch (ret) {
    case EBUSY:
        return -LockBusy;

    case SUCCESS:
        return SUCCESS;

    default:
        return -LockFail;
    }
}

String _WriteLock::getName() { return mName; }

int _WriteLock::lock(long timeInterval) {
    struct timespec ts;
    st(System)::getNextTime(timeInterval, &ts);

    if (pthread_rwlock_timedwrlock(&rwlock->rwlock, &ts) == ETIMEDOUT) {
        return -WaitTimeout;
    }

    return 0;
}

//------------ ReadWriteLock ------------
_ReadWriteLock::_ReadWriteLock() : _ReadWriteLock(nullptr) {}

_ReadWriteLock::_ReadWriteLock(String s) {
    pthread_rwlock_init(&rwlock, nullptr);
    mName = s;
}

sp<_ReadLock> _ReadWriteLock::getReadLock() {
    _ReadLock *l = new _ReadLock(AutoClone(this), mName);
    return AutoClone(l);
}

sp<_WriteLock> _ReadWriteLock::getWriteLock() {
    _WriteLock *l = new _WriteLock(AutoClone(this), mName);
    return AutoClone(l);
}

String _ReadWriteLock::getName() { 
    return mName; 
}

_ReadWriteLock::~_ReadWriteLock() { 
    pthread_rwlock_destroy(&rwlock); 
}

} // namespace obotcha
