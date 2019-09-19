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
        //printf("auto mutex1 lock,mutex is %x \n",mutex_t->getMutex_t());
        lock->lock();
        mutex_t = lock;
        //printf("auto mutex1 lock,after mutex is %x \n",mutex_t->getMutex_t());
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