#ifndef __OBOTCHA_READ_WRITE_HPP__
#define __OBOTCHA_READ_WRITE_HPP__

#include <pthread.h>
#include <sys/time.h>

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

class _ReadWriteLock;

DECLARE_SIMPLE_CLASS(ReadLock) {
public:
    friend class _ReadWriteLock;

    void lock();

    void unlock();

    int tryLock();

    int lock(long);

    String getName();

private:
    _ReadLock(sp<_ReadWriteLock>,String);

    sp<_ReadWriteLock> rwlock;

    String mName;
};

DECLARE_SIMPLE_CLASS(WriteLock) {
public:
    friend class _ReadWriteLock;

    void lock();

    void unlock();

    int tryLock();

    int lock(long);

    String getName();

private:
    _WriteLock(sp<_ReadWriteLock>,String);

    sp<_ReadWriteLock> rwlock;

    String mName;
};

DECLARE_SIMPLE_CLASS(ReadWriteLock) {

public:
    friend class _WriteLock;

    friend class _ReadLock;

    _ReadWriteLock();

    _ReadWriteLock(String);

    sp<_ReadLock> getReadLock();

    sp<_WriteLock> getWriteLock();

    String getName();

    void destroy();

private:
    pthread_rwlock_t rwlock;
    String mName;

    sp<_WriteLock> mWriteLock;
    sp<_ReadLock> mReadLock;
};

}
#endif