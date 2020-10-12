#include <pthread.h>
#include <errno.h>

#include "StrongPointer.hpp"
#include "ReadWriteLock.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

//------------ ReadLock ------------//
_ReadLock::_ReadLock(_ReadWriteLock *l) {
    rwlock.set_pointer(l);
}

_ReadLock::_ReadLock(_ReadWriteLock *l,String s) {
    rwlock.set_pointer(l);
    mName = s;
}

void _ReadLock::lock() {
    pthread_rwlock_rdlock(&rwlock->rwlock);
}

void _ReadLock::unlock() {
    pthread_rwlock_unlock(&rwlock->rwlock);  
}

int _ReadLock::tryLock() {
    int ret = pthread_rwlock_tryrdlock(&rwlock->rwlock);
    if(ret == 0) {
      return 0;
    }

    return -1;
}

String _ReadLock::getName() {
    return mName;
}

int _ReadLock::lock(long timeInterval) {
    struct timespec ts;

    st(System)::getNextTime(timeInterval,&ts);
    int ret = pthread_rwlock_timedrdlock(&rwlock->rwlock,&ts);
    if(ret == ETIMEDOUT) {
      return -WaitTimeout;
    }

    return 0;
}

//------------ WriteLock ------------//
_WriteLock::_WriteLock(_ReadWriteLock *l) {
  rwlock.set_pointer(l);
}

_WriteLock::_WriteLock(_ReadWriteLock *l,String s) {
    rwlock.set_pointer(l);
    mName = s;
}

void _WriteLock::lock() {
  pthread_rwlock_wrlock(&rwlock->rwlock);
}

void _WriteLock::unlock() {
  pthread_rwlock_unlock(&rwlock->rwlock);
}

int _WriteLock::tryLock() {
  int ret = pthread_rwlock_trywrlock(&rwlock->rwlock);
  if(ret == 0) {
    return 0;
  }

  return -1;
}

String _WriteLock::getName() {
    return mName;
}

int _WriteLock::lock(long timeInterval) {
    struct timespec ts;

    st(System)::getNextTime(timeInterval,&ts);
    int ret = pthread_rwlock_timedwrlock(&rwlock->rwlock,&ts);
    if(ret == ETIMEDOUT) {
      return -WaitTimeout;
    }

    return 0;
}

//------------ ReadWriteLock ------------//
_ReadWriteLock::_ReadWriteLock() {
    pthread_rwlock_init(&rwlock, NULL);
}

_ReadWriteLock::_ReadWriteLock(String s) {
    pthread_rwlock_init(&rwlock, NULL);
    mName = s;
}

sp<_ReadLock> _ReadWriteLock::getReadLock() {
    return createReadLock(this,mName);
}

sp<_WriteLock> _ReadWriteLock::getWriteLock() {
    return createWriteLock(this,mName);
}

String _ReadWriteLock::getName() {
    return mName;
}

void _ReadWriteLock::destroy() {
    pthread_rwlock_destroy(&rwlock);
}

}
