/**
 * @file Condition.cpp
 * @brief Causes the current thread to wait until it is signalled
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <pthread.h>

#include "Object.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

_Condition::_Condition():cond_t(PTHREAD_COND_INITIALIZER) {
    //mIsInterrupt = false;
}

void _Condition::wait(Mutex m) {
    pthread_mutex_t* mutex_t = m->getMutex_t();
    pthread_cond_wait(&cond_t,m->getMutex_t());
    
}

int _Condition::wait(Mutex m,long int timeInterval) {
    pthread_mutex_t* mutex_t = m->getMutex_t();
    if(timeInterval == 0) {
        return pthread_cond_wait(&cond_t,m->getMutex_t());
    }

    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    if(pthread_cond_timedwait(&cond_t,mutex_t,&ts) == ETIMEDOUT) {
        return -WaitTimeout;
    }
    return 0;
}

void _Condition::notify() {
    pthread_cond_signal(&cond_t);
}

void _Condition::notifyAll() {
    pthread_cond_broadcast(&cond_t);
}

void _Condition::interrupt() {
    notifyAll();
}

_Condition::~_Condition() {
    pthread_cond_destroy(&cond_t);
}

}