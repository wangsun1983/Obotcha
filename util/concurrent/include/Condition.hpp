#ifndef __OBOTCHA_CONDITION_HPP__
#define __OBOTCHA_CONDITION_HPP__

#include <atomic>
#include <pthread.h>
#include <functional>

#include "Object.hpp"
#include "AutoLock.hpp"

namespace obotcha {

class _Mutex;

DECLARE_CLASS(Condition) {
public:
    _Condition();

    ~_Condition();

    int wait(sp<_Mutex> m, long int millseconds = 0);
    int wait(AutoLock &m, long int millseconds = 0);
    
    int wait(sp<_Mutex> m,std::function<bool()> p);
    int wait(AutoLock & m,std::function<bool()> p);

    int wait(sp<_Mutex> m,long int millseconds,std::function<bool()> p);
    int wait(AutoLock & m,long int millseconds,std::function<bool()> p);

    void notify();

    void notifyAll();

private:
    pthread_cond_t cond_t;
};

} // namespace obotcha
#endif