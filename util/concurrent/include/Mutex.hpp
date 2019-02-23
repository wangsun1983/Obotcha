#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

DECLARE_SIMPLE_CLASS(Mutex) 
{
public:
    _Mutex();

    void lock();

    void unlock();

    bool trylock();

    pthread_mutex_t *getMutex_t(); 

private:
    pthread_mutex_t mutex_t;
};

#endif