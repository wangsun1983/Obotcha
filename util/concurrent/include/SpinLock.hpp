#ifndef __OBOTCHA_SPIN_LOCK_HPP__
#define __OBOTCHA_SPIN_LOCK_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "Lock.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(SpinLock) IMPLEMENTS(Lock) {
  public:
    _SpinLock(String);

    _SpinLock(const char *);

    _SpinLock();

    int lock();

    int unlock();

    int tryLock();

    ~_SpinLock();

    String toString();

  private:
    String mSpinLockName;

    pthread_spinlock_t mLock;
};

} // namespace obotcha
#endif