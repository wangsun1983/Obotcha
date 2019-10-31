#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>


#include "Mutex.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

//pthread_mutex_t _Mutex::mMapLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _Mutex::mGenLock = PTHREAD_MUTEX_INITIALIZER;

//std::map<std::uint64_t,pthread_t> * _Mutex::mOwners = nullptr;// = new std::map<std::uint64_t,pthread_t>();//use heap to save.no need to release
std::uint64_t _Mutex::mId = 1;

//----------- LocalAutoLock -----------
LocalAutoLock::LocalAutoLock(pthread_mutex_t *t) {
    pthread_mutex_lock(t);
    mutex_t = t;
}

LocalAutoLock::~LocalAutoLock() {
    pthread_mutex_unlock(mutex_t);
}

//----------- Mutex -----------
_Mutex::_Mutex(){
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE); 
    pthread_mutex_init(&mutex_t, &mutex_attr);
}

_Mutex::_Mutex(String v):_Mutex{}{
    mMutexName = v;
}

_Mutex::_Mutex(const char *v):_Mutex{}{
    mMutexName = createString(v);
}

pthread_mutex_t* _Mutex::getMutex_t() {
    return &mutex_t;
}

int _Mutex::lock() {

    //if(mutex_t.__data.__owner == syscall(SYS_gettid)) {
    //    return 0;
    //}

    if(pthread_mutex_lock(&mutex_t) == 0) {
        return 0;
    }
    return -1;
}

int _Mutex::lock(long timeInterval) {
    struct timespec ts;

    //if(mutex_t.__data.__owner == syscall(SYS_gettid)) {
    //    return 0;
    //}

    st(System)::getNextTime(timeInterval,&ts);
    int result = pthread_mutex_timedlock(&mutex_t,&ts);
    switch(result) {
        case ETIMEDOUT:
        return -WaitTimeout;
        
        case 0:
        default:
        return 0;
    }

    return -1;
}


int _Mutex::unlock() {
    if(pthread_mutex_unlock(&mutex_t) == 0) {
        return 0;
    }

    return -1;
}

int _Mutex::trylock() {
    //if(mutex_t.__data.__owner == syscall(SYS_gettid)) {
    //    return 0;
    //}

    if(pthread_mutex_trylock(&mutex_t) == 0) {
        return 0;
    }

    return -1;
}

String _Mutex::toString() {
    return mMutexName;
}

_Mutex::~_Mutex() {
    pthread_mutex_destroy(&mutex_t);
}



}