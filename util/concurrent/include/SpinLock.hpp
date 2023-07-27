#ifndef __OBOTCHA_SPIN_LOCK_HPP__
#define __OBOTCHA_SPIN_LOCK_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "Lock.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(SpinLock) IMPLEMENTS(Lock) {
  public:
    explicit _SpinLock(String);

    explicit _SpinLock(const char *);

    _SpinLock();

    int lock(long interval = 0) override;

    int unlock() override;

    int tryLock();

    ~_SpinLock() override;

    String toString() override;

  private:
    String mSpinLockName;

    pthread_spinlock_t mLock;
};

} // namespace obotcha
#endif