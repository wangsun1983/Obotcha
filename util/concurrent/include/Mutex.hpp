#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "AtomicBoolean.hpp"
#include "HashMap.hpp"

namespace obotcha {

class LocalAutoLock {
public:    
    LocalAutoLock(pthread_mutex_t *);
    ~LocalAutoLock();

private:
    pthread_mutex_t *mutex_t;
};

DECLARE_SIMPLE_CLASS(Mutex) {
public:
    _Mutex(String);

    _Mutex(const char *);

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
    pthread_mutexattr_t mutex_attr;

    String mMutexName;


    //static pthread_mutex_t mMapLock;
    //static std::map<std::uint64_t,pthread_t> *mOwners;
    //static pthread_mutex_t mGenLock;
    //static std::uint64_t generateId();
    //static std::uint64_t mId;
};

}
#endif