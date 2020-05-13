#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Lock.hpp"
#include "String.hpp"
#include "SpinLock.hpp"


namespace obotcha {

_SpinLock::_SpinLock(String n) {
    mSpinLockName = n;
}

_SpinLock::_SpinLock(const char *n) {
    mSpinLockName = createString(n);
}

_SpinLock::_SpinLock() {

}

int _SpinLock::lock() {
    while(mflag.test_and_set(std::memory_order_acquire));
}

int _SpinLock::unlock() {
    mflag.clear(std::memory_order_release);
}

_SpinLock::~_SpinLock() {}

String _SpinLock::toString() {
    return mSpinLockName;
}



}
