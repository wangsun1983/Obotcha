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
#include "Log.hpp"

namespace obotcha {

//------------ ReadLock ------------
_ReadLock::_ReadLock(sp<_ReadWriteLock> l, String s) {
    this->rwlock = l;
    mName = s;
}

int _ReadLock::lock() {
    if(rwlock->rwOwner == st(System)::myTid()) {
        LOG(ERROR)<<"Read lock acquire error,this thread already own write lock";
        return -1;
    }
    return -pthread_rwlock_rdlock(&rwlock->rwlock);
}

int _ReadLock::unlock() {
    if(rwlock->rwOwner == st(System)::myTid()) {
        LOG(ERROR)<<"Read lock release error,this thread already own write lock";
        return -1;
    }

    return -pthread_rwlock_unlock(&rwlock->rwlock);
}

int _ReadLock::tryLock() {
    if(rwlock->rwOwner == st(System)::myTid()) {
        LOG(ERROR)<<"Read lock acquire error,this thread already own write lock";
        return -1;
    }
    return -pthread_rwlock_tryrdlock(&rwlock->rwlock);
}

String _ReadLock::getName() { 
    return mName; 
}

int _ReadLock::lock(long timeInterval) {
    if(rwlock->rwOwner == st(System)::myTid()) {
        LOG(ERROR)<<"Read lock acquire error,this thread already own write lock";
        return -1;
    }
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
    int result = -pthread_rwlock_wrlock(&rwlock->rwlock);
    if(result == 0) {
        rwlock->rwOwner = st(System)::myTid();
    }
    return result;
}

int _WriteLock::unlock() {
    if(rwlock->rwOwner == st(System)::myTid()) {
        rwlock->rwOwner = 0;
    }
    
    return -pthread_rwlock_unlock(&rwlock->rwlock);
    
}

int _WriteLock::tryLock() {
    int result = -pthread_rwlock_trywrlock(&rwlock->rwlock);
    if(result == 0) {
        rwlock->rwOwner = st(System)::myTid();
    }
    return result;
}

String _WriteLock::getName() { 
    return mName;
}

int _WriteLock::lock(long timeInterval) {
    struct timespec ts = {0};
    st(System)::getNextTime(timeInterval, &ts);
    int ret = -pthread_rwlock_timedwrlock(&rwlock->rwlock, &ts);
    if(ret == 0) {
        rwlock->rwOwner = st(System)::myTid();
    }
    return ret;
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
