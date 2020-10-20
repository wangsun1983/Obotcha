#ifndef __OBOTCHA_MUTEX_HPP__
#define __OBOTCHA_MUTEX_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "Lock.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Mutex) IMPLEMENTS(Lock) {
public:
    friend class _Condition;
    
    _Mutex(String);

    _Mutex(const char *);

    _Mutex();

    int lock();

    int lock(long);

    int unlock();

    int trylock();

    ~_Mutex();

    String toString();

private:
    pthread_mutex_t *getMutex_t();

    pthread_mutex_t mutex_t;

    pthread_mutexattr_t mutex_attr;

    String mMutexName;
};

}
#endif