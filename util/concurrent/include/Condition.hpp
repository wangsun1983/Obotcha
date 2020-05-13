#ifndef __OBOTCHA_CONDITION_HPP__
#define __OBOTCHA_CONDITION_HPP__

#include <pthread.h>
#include <sys/time.h>

#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "StrongPointer.hpp"

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