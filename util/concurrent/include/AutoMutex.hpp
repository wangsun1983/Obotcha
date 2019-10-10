#ifndef __AUTO_MUTEX_HPP__
#define __AUTO_MUTEX_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"

namespace obotcha {

class AutoMutex {
public:
    AutoMutex(Mutex lock){
        lock->lock();
        mutex_t = lock;
    }

    AutoMutex(Mutex lock,long v) {
        lock->lock(v);
        mutex_t = lock;
    }

    ~AutoMutex() {
        mutex_t->unlock();
    }

private:
    Mutex mutex_t;
};

}
#endif