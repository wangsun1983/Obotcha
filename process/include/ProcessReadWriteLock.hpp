#ifndef __OBOTCHA_PROCESS_READ_WRITE_HPP__
#define __OBOTCHA_PROCESS_READ_WRITE_HPP__

#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Object.hpp"
#include "String.hpp"
#include "Lock.hpp"
#include "Concurrent.hpp"

namespace obotcha {

class _ProcessReadWriteLock;

DECLARE_CLASS(ProcessReadLock) IMPLEMENTS(Lock) {
  public:
    friend class _ProcessReadWriteLock;

    int lock(long interval = st(Concurrent)::kWaitForEver) override;
    int unlock() override;
    int tryLock();

  private:
    explicit _ProcessReadLock(sp<_ProcessReadWriteLock>);
    sp<_ProcessReadWriteLock> rwlock;
};

DECLARE_CLASS(ProcessWriteLock) IMPLEMENTS(Lock) {
  public:
    friend class _ProcessReadWriteLock;

    int lock(long interval = st(Concurrent)::kWaitForEver) override;
    int unlock() override;
    int tryLock();
    
  private:
    explicit _ProcessWriteLock(sp<_ProcessReadWriteLock>);
    sp<_ProcessReadWriteLock> rwlock;
};

DECLARE_CLASS(ProcessReadWriteLock) {
  public:
    friend class _ProcessWriteLock;
    friend class _ProcessReadLock;

    explicit _ProcessReadWriteLock(String name);
    sp<_ProcessReadLock> getReadLock();
    sp<_ProcessWriteLock> getWriteLock();
    //String getPath();
    ~_ProcessReadWriteLock() override;

    static void Clear(String name);
    static void Create(String name);

  private:
    String mName;
    int mRwlockFd = -1;
    pthread_rwlock_t *mRwlock = nullptr;
    //FileDescriptor mFd;
};

}
#endif
