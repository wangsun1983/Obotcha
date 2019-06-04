#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Mutex) 
{
public:
    _Mutex(String);

    _Mutex();

    void lock();

    void unlock();

    bool trylock();

    pthread_mutex_t *getMutex_t();

    ~_Mutex();

private:
    pthread_mutex_t mutex_t;

    String mMutexName;
};

}
#endif