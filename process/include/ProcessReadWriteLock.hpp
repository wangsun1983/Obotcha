#ifndef __OBOTCHA_PROCESS_READ_WRITE_HPP__
#define __OBOTCHA_PROCESS_READ_WRITE_HPP__

#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Object.hpp"
#include "String.hpp"
#include "Lock.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

class _ProcessReadWriteLock;

DECLARE_CLASS(ProcessReadLock) IMPLEMENTS(Lock) {
  public:
    friend class _ProcessReadWriteLock;

    int lock(long interval = 0) override;
    int unlock() override;
    //String getPath();

  private:
    explicit _ProcessReadLock(sp<_ProcessReadWriteLock>);
    sp<_ProcessReadWriteLock> rwlock;
};

DECLARE_CLASS(ProcessWriteLock) IMPLEMENTS(Lock) {
  public:
    friend class _ProcessReadWriteLock;

    int lock(long interval = 0) override;
    int unlock() override;
    //String getPath();

  private:
    explicit _ProcessWriteLock(sp<_ProcessReadWriteLock>);
    sp<_ProcessReadWriteLock> rwlock;
};

DECLARE_CLASS(ProcessReadWriteLock) {
  public:
    friend class _ProcessWriteLock;
    friend class _ProcessReadLock;

    explicit _ProcessReadWriteLock(String);
    sp<_ProcessReadLock> getReadLock();
    sp<_ProcessWriteLock> getWriteLock();
    //String getPath();
    ~_ProcessReadWriteLock() override;

    static void Clear(String id);
    static void Create(String id);

  private:
    String mRwId;
    int mRwlockFd = -1;
    pthread_rwlock_t *mRwlock = nullptr;
    //FileDescriptor mFd;
};

}
#endif
