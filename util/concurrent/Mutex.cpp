#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "Mutex.hpp"
#include "System.hpp"
#include "Log.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

_Mutex::_Mutex(st(Lock)::Type type):mType(type) {
    pthread_mutexattr_init(&mutex_attr);
    switch (type) {
        case st(Lock)::Type::Recursive:
            pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
            break;

        case st(Lock)::Type::Normal:
            pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_NORMAL);
            break;
    }

    pthread_mutex_init(&mutex_t, &mutex_attr);
}

_Mutex::_Mutex(String v, st(Lock)::Type type):_Mutex(type) {
    mMutexName = v;
}

_Mutex::_Mutex(const char *v, st(Lock)::Type type):_Mutex(type) {
    mMutexName = String::New(v);
}

bool _Mutex::isOwner() {
    return mutex_t.__data.__owner == syscall(SYS_gettid);
}

int _Mutex::lock(long timeInterval) {
    if (timeInterval == st(Concurrent)::kWaitForEver) {
        return -pthread_mutex_lock(&mutex_t);
    } else {
        struct timespec ts = {0};
        st(System)::GetNextTime(timeInterval, &ts);
        return -pthread_mutex_timedlock(&mutex_t, &ts);
    }
}

int _Mutex::unlock() {
    if(!isOwner()) {
        Trigger(IllegalStateException,"spinlock wrong owner")
    }
    return -pthread_mutex_unlock(&mutex_t);
}

int _Mutex::tryLock() {
    return -pthread_mutex_trylock(&mutex_t);
}

String _Mutex::getName() { 
    return mMutexName; 
}

pthread_mutex_t *_Mutex::getMutex_t() { 
    return &mutex_t; 
}

st(Lock)::Type _Mutex::getType() {
    return mType;
}

_Mutex::~_Mutex() {
    pthread_mutex_destroy(&mutex_t);
    pthread_mutexattr_destroy(&mutex_attr);
}

} // namespace obotcha