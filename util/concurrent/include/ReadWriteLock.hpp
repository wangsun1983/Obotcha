#ifndef __READ_WRITE_HPP__
#define __READ_WRITE_HPP__

#include <pthread.h>
#include <sys/time.h>

#include "StrongPointer.hpp"
#include "Object.hpp"

namespace obotcha {

class _ReadWriteLock;

DECLARE_SIMPLE_CLASS(ReadLock) {
public:
    _ReadLock(_ReadWriteLock *);

    void lock();

    void unlock();

private:
    sp<_ReadWriteLock> rwlock;
};

DECLARE_SIMPLE_CLASS(WriteLock) {
public:
    _WriteLock(_ReadWriteLock *);

    void lock();

    void unlock();

private:
    sp<_ReadWriteLock> rwlock;
};

DECLARE_SIMPLE_CLASS(ReadWriteLock) {

public:
    friend class _WriteLock;

    friend class _ReadLock;

    _ReadWriteLock();

    sp<_ReadLock> getReadLock();

    sp<_WriteLock> getWriteLock(); 

    void destroy();

private:
    pthread_rwlock_t rwlock;
};

}
#endif