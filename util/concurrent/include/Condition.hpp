#ifndef __OBOTCHA_CONDITION_HPP__
#define __OBOTCHA_CONDITION_HPP__

#include <atomic>
#include <pthread.h>

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

    void notify();

    void notifyAll();

private:
    pthread_cond_t cond_t;
};

} // namespace obotcha
#endif