#ifndef __OBOTCHA_CONDITION_HPP__
#define __OBOTCHA_CONDITION_HPP__

#include <pthread.h>
#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _Mutex;
class _Thread;

DECLARE_SIMPLE_CLASS(Condition) {

public:
    friend class _Thread;
    friend void doThreadExit(_Thread *thread);

    _Condition();
    
    ~_Condition();

    void wait(sp<_Mutex> m);
    
    int wait(sp<_Mutex> m,long int millseconds);
    
    void notify();
    
    void notifyAll();

private:
    pthread_cond_t cond_t;
    void waitExit();
    bool waitEnter();
    
    void interrupt();
    //std::atomic<bool> mIsInterrupt;

    //sp<_Mutex> mWaitMutex;
};

}
#endif