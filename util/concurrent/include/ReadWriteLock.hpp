#ifndef __OBOTCHA_READ_WRITE_HPP__
#define __OBOTCHA_READ_WRITE_HPP__

#include <pthread.h>
#include <sys/time.h>
#include <map>

#include "Lock.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

namespace obotcha {

class _ReadWriteLock;

DECLARE_CLASS(ReadLock) IMPLEMENTS(Lock) {
  public:
    friend class _ReadWriteLock;

    int lock();

    int unlock();

    int tryLock();

    int lock(long);

    String getName();

  private:
    _ReadLock(sp<_ReadWriteLock>, String);

    sp<_ReadWriteLock> rwlock;

    String mName;
};

DECLARE_CLASS(WriteLock) IMPLEMENTS(Lock) {
  public:
    friend class _ReadWriteLock;

    int lock();

    int unlock();

    int tryLock();

    int lock(long);

    String getName();

  private:
    _WriteLock(sp<_ReadWriteLock>, String);

    sp<_ReadWriteLock> rwlock;

    String mName;
};

DECLARE_CLASS(ReadWriteLock) {

  public:
    friend class _WriteLock;

    friend class _ReadLock;

    _ReadWriteLock();

    _ReadWriteLock(String);

    sp<_ReadLock> getReadLock();

    sp<_WriteLock> getWriteLock();

    String getName();

    bool isOwner();

    ~_ReadWriteLock();

  private:
    int mWriteReqCount;
    bool mIsWrite;
    int mWrOwner;
    int mOwnerCount;
    //<tid,counts>
    std::map<int,int> readOwners;

    Mutex mMutex;
    Condition mReadCondition;
    Condition mWriteCondition;

    String mName;

    int _readlock();

    int _unReadlock();

    int _tryReadLock();

    int _readlock(long);

    int _writelock();

    int _unWritelock();

    int _tryWriteLock();

    int _writelock(long);
};

} // namespace obotcha
#endif