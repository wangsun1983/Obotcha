/**
 * @file Mutex.cpp
 * @brief  Mutex is a tool for controlling access to a shared resource by
 * multiple threads
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "Error.hpp"
#include "Mutex.hpp"
#include "System.hpp"

namespace obotcha {

//----------- Mutex -----------
_Mutex::_Mutex(int type) {
    pthread_mutexattr_init(&mutex_attr);
    switch (type) {
        case Recursive:
            pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
            break;

        case Normal:
            pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_NORMAL);
            break;
    }

    pthread_mutex_init(&mutex_t, &mutex_attr);
}

_Mutex::_Mutex(String v, int type) : _Mutex(type) { 
    mMutexName = v; 
}

_Mutex::_Mutex(const char *v, int type) : _Mutex(type) {
    mMutexName = createString(v);
}

int _Mutex::lock() {
    //printf("owner is %d \n",mutex_t.__data.__owner);
    return (pthread_mutex_lock(&mutex_t) == 0)? 0:-LockFail;
}

int _Mutex::lock(long timeInterval) {
    struct timespec ts;

    // if(mutex_t.__data.__owner == syscall(SYS_gettid)) {
    //    return 0;
    //}
    if (timeInterval == 0) {
        return pthread_mutex_lock(&mutex_t);
    }

    st(System)::getNextTime(timeInterval, &ts);
    int result = pthread_mutex_timedlock(&mutex_t, &ts);
    if (result == ETIMEDOUT) {
        return -WaitTimeout;
    }

    return 0;
}

int _Mutex::unlock() {
    switch(pthread_mutex_unlock(&mutex_t)) {
        case EINVAL:
        return -UnLockInvalid;

        case EFAULT:
        return -UnLockFail;

        case EPERM:
        return -UnLockPerm;
    }
    
    return SUCCESS;
}

int _Mutex::tryLock() {
    int ret = pthread_mutex_trylock(&mutex_t);
    switch (ret) {
    case EBUSY:
        return -LockBusy;

    default:
        return -LockFail;
    }
    return SUCCESS;
}

String _Mutex::toString() { 
    return mMutexName; 
}

pthread_mutex_t *_Mutex::getMutex_t() { 
    return &mutex_t; 
}

_Mutex::~_Mutex() {
    pthread_mutex_destroy(&mutex_t);
    pthread_mutexattr_destroy(&mutex_attr);
}

} // namespace obotcha