#ifndef __OBOTCHA_PROCESS_READ_WRITE_HPP__
#define __OBOTCHA_PROCESS_READ_WRITE_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "Lock.hpp"

namespace obotcha {

class _ProcessReadWriteLock;

DECLARE_CLASS(ProcessReadLock) IMPLEMENTS(Lock) {
  public:
    friend class _ProcessReadWriteLock;

    int lock();

    int unlock();

    String getPath();

  private:
    _ProcessReadLock(sp<_ProcessReadWriteLock>);

    sp<_ProcessReadWriteLock> rwlock;
};

DECLARE_CLASS(ProcessWriteLock) IMPLEMENTS(Lock) {
  public:
    friend class _ProcessReadWriteLock;

    int lock();

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
    int fd;
};

}
#endif