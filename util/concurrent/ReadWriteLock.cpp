#include <pthread.h>

#include "StrongPointer.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

//------------ ReadLock ------------//
_ReadLock::_ReadLock(_ReadWriteLock *l) {
    rwlock.set_pointer(l);
}

void _ReadLock::lock() {
  pthread_rwlock_rdlock(&rwlock->rwlock);
}

void _ReadLock::unlock() {
  pthread_rwlock_unlock(&rwlock->rwlock);  
}

//------------ WriteLock ------------//
_WriteLock::_WriteLock(_ReadWriteLock *l) {
  rwlock.set_pointer(l);
}

void _WriteLock::lock() {
  pthread_rwlock_wrlock(&rwlock->rwlock);
}

void _WriteLock::unlock() {
  pthread_rwlock_unlock(&rwlock->rwlock);
}

//------------ ReadWriteLock ------------//
_ReadWriteLock::_ReadWriteLock() {
    pthread_rwlock_init(&rwlock, NULL);
}

sp<_ReadLock> _ReadWriteLock::getReadLock() {
    return createReadLock(this);
}

sp<_WriteLock> _ReadWriteLock::getWriteLock() {
    return createWriteLock(this);
}

void _ReadWriteLock::destroy() {
    pthread_rwlock_destroy(&rwlock);
}

}
