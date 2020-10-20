/**
 * @file Mutex.cpp
 * @brief  Mutex is a tool for controlling access to a shared resource by multiple threads
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "Mutex.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

//----------- Mutex -----------
_Mutex::_Mutex(){
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE); 
    pthread_mutex_init(&mutex_t, &mutex_attr);
}

_Mutex::_Mutex(String v):_Mutex(){
    mMutexName = v;
}

_Mutex::_Mutex(const char *v):_Mutex(){
    mMutexName = createString(v);
}

int _Mutex::lock() {

    //if(mutex_t.__data.__owner == syscall(SYS_gettid)) {
    //    return 0;
    //}

    return pthread_mutex_lock(&mutex_t);
}

int _Mutex::lock(long timeInterval) {
    struct timespec ts;

    //if(mutex_t.__data.__owner == syscall(SYS_gettid)) {
    //    return 0;
    //}

    st(System)::getNextTime(timeInterval,&ts);
    if(pthread_mutex_timedlock(&mutex_t,&ts) == ETIMEDOUT) {
        return -WaitTimeout;
    }

    return 0;
}


int _Mutex::unlock() {
    return pthread_mutex_unlock(&mutex_t);
}

int _Mutex::trylock() {
    //if(mutex_t.__data.__owner == syscall(SYS_gettid)) {
    //    return 0;
    //}

    return pthread_mutex_trylock(&mutex_t);
}

String _Mutex::toString() {
    return mMutexName;
}

pthread_mutex_t *_Mutex::getMutex_t() {
    return &mutex_t;
}

_Mutex::~_Mutex() {
    pthread_mutex_destroy(&mutex_t);
}



}