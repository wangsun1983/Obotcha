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
    mIsInterrupt = false;
}

void _Condition::wait(Mutex m) {
    if(!waitEnter()) {
        return;
    }

    pthread_mutex_t* mutex_t = m->getMutex_t();
    pthread_cond_wait(&cond_t,m->getMutex_t());
    waitExit();
}

int _Condition::wait(Mutex m,long int timeInterval) {
    if(!waitEnter()) {
        return -InvalidStatus;
    }
    pthread_mutex_t* mutex_t = m->getMutex_t();
    if(timeInterval == 0) {
        return pthread_cond_wait(&cond_t,m->getMutex_t());
    }

    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    if(pthread_cond_timedwait(&cond_t,mutex_t,&ts) == ETIMEDOUT) {
        return -WaitTimeout;
    }
    
    waitExit();

    return 0;
}

void _Condition::notify() {
    pthread_cond_signal(&cond_t);
}

void _Condition::notifyAll() {
    pthread_cond_broadcast(&cond_t);
}

void _Condition::interrupt() {
    mIsInterrupt = true;
    notifyAll();
}

_Condition::~_Condition() {
    pthread_cond_destroy(&cond_t);
}

bool _Condition::waitEnter() {

    if(!mIsInterrupt) {
        Thread t = st(Thread)::current();
        if(t != nullptr) {
            t->setCurrentWaitCondition(AutoClone(this));
        }
        return true;
    }
    return false;
}

void _Condition::waitExit() {
    if(mIsInterrupt) {
        Thread t = st(Thread)::current();
        Condition c = t->getCurrentWaitCondition();
        if(c != nullptr && c == AutoClone(this)) {
            Trigger(InterruptedException,"thread notify!!!");
        }
    }

    Thread t = st(Thread)::current();
    if(t != nullptr) {
        t->setCurrentWaitCondition(NullData<Condition>());
    }
}

}