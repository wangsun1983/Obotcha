/**
 * @file ReadWriteLock.cpp
 * @brief  ReadWriteLock is a tool for read/write access to a shared resource by multiple threads
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <pthread.h>

#include "StrongPointer.hpp"
#include "ReadWriteLock.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

//------------ ReadLock ------------
_ReadLock::_ReadLock(sp<_ReadWriteLock> l,String s) {
    this->rwlock = l;
    mName = s;
}

void _ReadLock::lock() {
    pthread_rwlock_rdlock(&rwlock->rwlock);
}

void _ReadLock::unlock() {
    pthread_rwlock_unlock(&rwlock->rwlock);  
}

int _ReadLock::tryLock() {
    return pthread_rwlock_tryrdlock(&rwlock->rwlock);
}

String _ReadLock::getName() {
    return mName;
}

int _ReadLock::lock(long timeInterval) {
    struct timespec ts;

    st(System)::getNextTime(timeInterval,&ts);
    if(pthread_rwlock_timedrdlock(&rwlock->rwlock,&ts) == ETIMEDOUT) {
        return -WaitTimeout;
    }

    return 0;
}

//------------ WriteLock ------------//
_WriteLock::_WriteLock(sp<_ReadWriteLock> l,String s) {
    rwlock = l;
    mName = s;
}

void _WriteLock::lock() {
    pthread_rwlock_wrlock(&rwlock->rwlock);
}

void _WriteLock::unlock() {
    pthread_rwlock_unlock(&rwlock->rwlock);
}

int _WriteLock::tryLock() {
    return pthread_rwlock_trywrlock(&rwlock->rwlock);
}

String _WriteLock::getName() {
    return mName;
}

int _WriteLock::lock(long timeInterval) {
    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    
    if(pthread_rwlock_timedwrlock(&rwlock->rwlock,&ts) == ETIMEDOUT) {
        return -WaitTimeout;
    }

    return 0;
}

//------------ ReadWriteLock ------------
_ReadWriteLock::_ReadWriteLock():_ReadWriteLock(nullptr) {
}

_ReadWriteLock::_ReadWriteLock(String s) {
    pthread_rwlock_init(&rwlock, NULL);
    mName = s;
}

sp<_ReadLock> _ReadWriteLock::getReadLock() {
    ReadLock lock;
    _ReadLock *l = new _ReadLock(AutoClone(this),mName);
    lock.set_pointer(l);
    return lock;
}

sp<_WriteLock> _ReadWriteLock::getWriteLock() {
    WriteLock lock;
    _WriteLock *l = new _WriteLock(AutoClone(this),mName);
    lock.set_pointer(l);
    return lock;
}

String _ReadWriteLock::getName() {
    return mName;
}

void _ReadWriteLock::destroy() {
    pthread_rwlock_destroy(&rwlock);
}

}
