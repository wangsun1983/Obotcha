#ifndef __OBOTCHA_CONDITION_HPP__
#define __OBOTCHA_CONDITION_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Condition) {

public:
    _Condition();

    void wait(Mutex m);
    
    int wait(Mutex m,long int millseconds);
    
    void notify();
    
    void notifyAll();

private:
    pthread_cond_t cond_t;
    
    Mutex  mMutex;
};

}
#endif