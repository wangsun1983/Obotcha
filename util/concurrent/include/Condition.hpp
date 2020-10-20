#ifndef __OBOTCHA_CONDITION_HPP__
#define __OBOTCHA_CONDITION_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _Mutex;

DECLARE_SIMPLE_CLASS(Condition) {

public:
    _Condition();
    
    ~_Condition();

    void wait(sp<_Mutex> m);
    
    int wait(sp<_Mutex> m,long int millseconds);
    
    void notify();
    
    void notifyAll();

private:
    pthread_cond_t cond_t;
};

}
#endif