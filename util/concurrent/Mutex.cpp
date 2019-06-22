#include <stdio.h>

#include "Mutex.hpp"

namespace obotcha {

_Mutex::_Mutex(){
    pthread_mutex_init(&mutex_t, NULL);
}

_Mutex::_Mutex(String v){
    pthread_mutex_init(&mutex_t, NULL);
    mMutexName = v;
}

pthread_mutex_t* _Mutex::getMutex_t() {
    return &mutex_t;
}

int _Mutex::lock() {
    if(pthread_mutex_lock(&mutex_t) == 0) {
        return 0;
    }

    return -MutexLockFail;
}

int _Mutex::lock(long timeInterval) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    long secs = timeInterval/1000;
    timeInterval = timeInterval%1000;

    long add = 0;
    timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
    add = timeInterval / (1000*1000*1000);
    ts.tv_sec += (add + secs);
    ts.tv_nsec = timeInterval%(1000*1000*1000);
    int result = pthread_mutex_timedlock(&mutex_t,&ts);
    switch(result) {
        case ETIMEDOUT:
        return -MutexLockTimedOut;
        
        case 0:
        return 0;
    }

    return -MutexLockFail;
}


int _Mutex::unlock() {
    if(pthread_mutex_unlock(&mutex_t) == 0) {
        return 0;
    }

    return -MutexUnlockFail;
}

int _Mutex::trylock() {
    if(pthread_mutex_trylock(&mutex_t) == 0) {
        return 0;
    }

    return -MutexTryLockFail;
}

String _Mutex::toString() {
    return mMutexName;
}

_Mutex::~_Mutex() {
    pthread_mutex_destroy(&mutex_t);
}



}