#ifndef __OBOTCHA_AUTO_LOCK_HPP__
#define __OBOTCHA_AUTO_LOCK_HPP__

#include <stdio.h>

#include "Lock.hpp"

namespace obotcha {

class _Condition;
class _ProcessCondition;

class AutoLock {
public:
    friend class _Condition;
    friend class _ProcessCondition;
    AutoLock(Lock lock){
        if(lock != nullptr) {
            lock->lock();
            mLock = lock;
        }
    }

    ~AutoLock() {
        if(mLock != nullptr) {
            mLock->unlock();
        }
    }

    void release() {
        if(mLock != nullptr) {
            mLock->unlock();
        }
    }

private:
    Lock mLock;
};

}
#endif
