#ifndef __AUTO_MUTEX_HPP__
#define __AUTO_MUTEX_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"

namespace obotcha {

class AutoMutex {
public:
    AutoMutex(Mutex lock)
        : mutex_t(lock) {
        //printf("auto mutex1 lock,mutex is %x \n",mutex_t->getMutex_t());
        mutex_t->lock();
        //printf("auto mutex1 lock,after mutex is %x \n",mutex_t->getMutex_t());
    }

    AutoMutex(Mutex lock,long v): mutex_t(lock) {
        lock->lock(v);
    }

    ~AutoMutex() {
        mutex_t->unlock();
    }

private:
    Mutex mutex_t;
};

}
#endif