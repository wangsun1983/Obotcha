#ifndef __OBOTCHA_SPIN_LOCK_HPP__
#define __OBOTCHA_SPIN_LOCK_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Lock.hpp"
#include "String.hpp"


namespace obotcha {

DECLARE_SIMPLE_CLASS(SpinLock) IMPLEMENTS(Lock) {
public:
    _SpinLock(String);

    _SpinLock(const char *);

    _SpinLock();

    int lock();

    int unlock();

    ~_SpinLock();

    String toString();

private:
    String mSpinLockName;

    pthread_spinlock_t mLock;
};

}
#endif