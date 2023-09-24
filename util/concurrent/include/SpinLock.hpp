#ifndef __OBOTCHA_SPIN_LOCK_HPP__
#define __OBOTCHA_SPIN_LOCK_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "Lock.hpp"
#include "String.hpp"
#include "Concurrent.hpp"

namespace obotcha {

DECLARE_CLASS(SpinLock) IMPLEMENTS(Lock) {
  public:
    explicit _SpinLock(String);

    explicit _SpinLock(const char *);

    _SpinLock();

    int lock(long interval = st(Concurrent)::kWaitForEver) override;

    int unlock() override;

    int tryLock();

    ~_SpinLock() override;

    String toString() override;

  private:
    String mSpinLockName;

    pthread_spinlock_t mLock;
    std::atomic_long mOwner;
};

} // namespace obotcha
#endif