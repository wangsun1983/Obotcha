#include <stdio.h>

#include "Mutex.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

pthread_mutex_t _Mutex::mMapLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _Mutex::mGenLock = PTHREAD_MUTEX_INITIALIZER;

std::map<std::uint64_t,pthread_t> *_Mutex::mOwners = new std::map<std::uint64_t,pthread_t>();//use heap to save.no need to release
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
std::uint64_t _Mutex::generateId() {
    LocalAutoLock ll(&mGenLock);
    mId++;
    return mId;
}

_Mutex::_Mutex(){
    pthread_mutex_init(&mutex_t, NULL);
    mutexId = generateId();
}

_Mutex::_Mutex(String v){
    pthread_mutex_init(&mutex_t, NULL);
    mMutexName = v;
    mutexId = generateId();
}

_Mutex::_Mutex(const char *v) {
    pthread_mutex_init(&mutex_t, NULL);
    mMutexName = createString(v);
    mutexId = generateId();
}

pthread_mutex_t* _Mutex::getMutex_t() {
    return &mutex_t;
}

int _Mutex::lock() {
    if(pthread_mutex_trylock(&mutex_t) == 0) {  
        {
            LocalAutoLock ll(&mMapLock);
            pthread_t current = pthread_self();
            mOwners->insert(std::pair<std::uint64_t,pthread_t>(mutexId,current));
        }

        return 0;
    }
    {
        LocalAutoLock ll(&mMapLock);
        auto iterator = mOwners->find(mutexId);
        if(iterator != mOwners->end() && iterator->second == pthread_self()) {
            return 0;
        }
    }
    if(pthread_mutex_lock(&mutex_t) == 0) {
        {
            LocalAutoLock ll(&mMapLock);
            pthread_t current = pthread_self();
            mOwners->insert(std::pair<std::uint64_t,pthread_t>(mutexId,current));
        }
        return 0;
    }
    return -1;
}

int _Mutex::lock(long timeInterval) {
    struct timespec ts;

    st(System)::getNextTime(timeInterval,&ts);

    int result = pthread_mutex_timedlock(&mutex_t,&ts);
    switch(result) {
        case ETIMEDOUT:
        return -WaitTimeout;
        
        case 0:
        {
            LocalAutoLock ll(&mMapLock);
            pthread_t current = pthread_self();
            mOwners->insert(std::pair<std::uint64_t,pthread_t>(mutexId,current));
        }
        return 0;
    }

    return -1;
}


int _Mutex::unlock() {
    //printf("unlock trace1 \n");
    {
        LocalAutoLock ll(&mMapLock);
        mOwners->erase(mutexId);
    }

    if(pthread_mutex_unlock(&mutex_t) == 0) {
        return 0;
    }

    return -1;
}

int _Mutex::trylock() {
    if(pthread_mutex_trylock(&mutex_t) == 0) {
        {
            LocalAutoLock ll(&mMapLock);
            pthread_t current = pthread_self();
            mOwners->insert(std::pair<std::uint64_t,pthread_t>(mutexId,current));
        }
        return 0;
    }

    return -1;
}

String _Mutex::toString() {
    return mMutexName;
}

_Mutex::~_Mutex() {
    {
        LocalAutoLock ll(&mMapLock);
        mOwners->erase(mutexId);
    }

    pthread_mutex_destroy(&mutex_t);
}



}