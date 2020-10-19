#ifndef __OBOTCHA_AUTO_LOCK_HPP__
#define __OBOTCHA_AUTO_LOCK_HPP__

#include <stdio.h>

#include "Lock.hpp"

namespace obotcha {

class AutoLock {
public:
    AutoLock(Lock lock){
        lock->lock();
        mLock = lock;
    }

    ~AutoLock() {
        mLock->unlock();
    }

private:
    Lock mLock;
};

}
#endif