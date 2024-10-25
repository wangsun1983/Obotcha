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

#ifndef __OBOTCHA_READ_WRITE_HPP__
#define __OBOTCHA_READ_WRITE_HPP__

#include <pthread.h>
#include <sys/time.h>
#include <map>

#include "Object.hpp"
#include "Lock.hpp"
#include "String.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

namespace obotcha {

class _ReadWriteLock;

DECLARE_CLASS(ReadLock) IMPLEMENTS(Lock) {
  public:
    friend class _ReadWriteLock;

    int unlock() override;

    int tryLock();

    int lock(long interval = st(Concurrent)::kWaitForEver) override;

    String getName();

  private:
    _ReadLock(sp<_ReadWriteLock>, String);

    sp<_ReadWriteLock> rwlock;

    String mName;
};

DECLARE_CLASS(WriteLock) IMPLEMENTS(Lock) {
  public:
    friend class _ReadWriteLock;

    int unlock() override;

    int tryLock();

    int lock(long interval = st(Concurrent)::kWaitForEver) override;

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

    _ReadWriteLock() = default;

    explicit _ReadWriteLock(String);

    sp<_ReadLock> getReadLock();

    sp<_WriteLock> getWriteLock();

    String getName();

    bool isOwner();

    ~_ReadWriteLock() override = default;

  private:
    int mWriteReqCount = 0;
    bool mIsWrite = false;
    long mWrOwner = -1;
    int mWrOwnerCount = 0;
    //<tid,counts>
    std::map<long,int> mReadOwners;

    Mutex mMutex = Mutex::New();
    Condition mReadCondition = Condition::New();
    Condition mWriteCondition = Condition::New();

    String mName;

    int _unReadlock();

    int _tryReadLock();

    int _readlock(long);

    int _unWritelock();

    int _tryWriteLock();

    int _writelock(long);
};

} // namespace obotcha
#endif