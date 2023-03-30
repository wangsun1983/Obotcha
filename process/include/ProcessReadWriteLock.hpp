#ifndef __OBOTCHA_PROCESS_READ_WRITE_HPP__
#define __OBOTCHA_PROCESS_READ_WRITE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "Lock.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

class _ProcessReadWriteLock;

DECLARE_CLASS(ProcessReadLock) IMPLEMENTS(Lock) {
  public:
    friend class _ProcessReadWriteLock;

    int lock(long interval = 0);
    int unlock();
    String getPath();

  private:
    _ProcessReadLock(sp<_ProcessReadWriteLock>);
    sp<_ProcessReadWriteLock> rwlock;
};

DECLARE_CLASS(ProcessWriteLock) IMPLEMENTS(Lock) {
  public:
    friend class _ProcessReadWriteLock;

    int lock(long interval = 0);
    int unlock();
    String getPath();

  private:
    _ProcessWriteLock(sp<_ProcessReadWriteLock>);
    sp<_ProcessReadWriteLock> rwlock;
};

DECLARE_CLASS(ProcessReadWriteLock) {
  public:
    friend class _ProcessWriteLock;
    friend class _ProcessReadLock;

    _ProcessReadWriteLock(String);
    sp<_ProcessReadLock> getReadLock();
    sp<_ProcessWriteLock> getWriteLock();
    String getPath();
    ~_ProcessReadWriteLock();

  private:
    String mPath;
    FileDescriptor mFd;
};

}
#endif
