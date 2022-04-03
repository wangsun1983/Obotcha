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
    return -pthread_rwlock_rdlock(&rwlock->rwlock);
}

int _ReadLock::unlock() {
    return -pthread_rwlock_unlock(&rwlock->rwlock);
}

int _ReadLock::tryLock() {
    return -pthread_rwlock_tryrdlock(&rwlock->rwlock);
}

String _ReadLock::getName() { 
    return mName; 
}

int _ReadLock::lock(long timeInterval) {
    struct timespec ts = {0};
    st(System)::getNextTime(timeInterval, &ts);
    return -pthread_rwlock_timedrdlock(&rwlock->rwlock, &ts);
}

//------------ WriteLock ------------//
_WriteLock::_WriteLock(sp<_ReadWriteLock> l, String s) {
    rwlock = l;
    mName = s;
}

int _WriteLock::lock() {
    return -pthread_rwlock_wrlock(&rwlock->rwlock);
}

int _WriteLock::unlock() {
    return -pthread_rwlock_unlock(&rwlock->rwlock);
}

int _WriteLock::tryLock() {
    return -pthread_rwlock_trywrlock(&rwlock->rwlock);
}

String _WriteLock::getName() { 
    return mName;
}

int _WriteLock::lock(long timeInterval) {
    struct timespec ts = {0};
    st(System)::getNextTime(timeInterval, &ts);
    return -pthread_rwlock_timedwrlock(&rwlock->rwlock, &ts);
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
