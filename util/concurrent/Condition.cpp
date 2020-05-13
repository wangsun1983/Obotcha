#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "Condition.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

_Condition::_Condition():cond_t(PTHREAD_COND_INITIALIZER) {
    //TODO nothing
}

void _Condition::wait(Mutex m) {
    mMutex = m;
    pthread_mutex_t* mutex_t = m->getMutex_t();
    pthread_cond_wait(&cond_t,mutex_t);
}

int _Condition::wait(Mutex m,long int timeInterval) {
    struct timespec ts;
    if(timeInterval == 0) {
        wait(m);
        return 0;
    }
    
    st(System)::getNextTime(timeInterval,&ts);
    mMutex = m;
    pthread_mutex_t* mutex_t = m->getMutex_t();
    int ret = pthread_cond_timedwait(&cond_t,mutex_t,&ts);
    if(ret == ETIMEDOUT) {
        return -WaitTimeout;
    }

    return 0;
}

void _Condition::notify() {
    //cond.notify_one();
    if(mMutex != nullptr) {
        AutoLock ll(mMutex);
        pthread_cond_signal(&cond_t);
    }
}

void _Condition::notifyAll() {
    //cond.notify_all();
    if(mMutex != nullptr) {
        AutoLock ll(mMutex);
        pthread_cond_broadcast(&cond_t);
    }
}

}