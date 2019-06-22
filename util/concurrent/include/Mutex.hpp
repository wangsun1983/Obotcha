#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {


enum MutexFailReason {
    MutexTryLockFail = 200,
    MutexLockFail,
    MutexUnlockFail,
    MutexLockTimedOut,
};


DECLARE_SIMPLE_CLASS(Mutex) 
{
public:
    _Mutex(String);

    _Mutex();

    int lock();

    int lock(long);

    int unlock();

    int trylock();

    pthread_mutex_t *getMutex_t();

    ~_Mutex();

    String toString();

private:
    pthread_mutex_t mutex_t;

    String mMutexName;
};

}
#endif