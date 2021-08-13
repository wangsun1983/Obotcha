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
#include "InitializeException.hpp"
#include "IllegalStateException.hpp"
namespace obotcha {

_Condition::_Condition() {
    if(pthread_cond_init(&cond_t, nullptr) != 0) {
        Trigger(InitializeException,"Condition error");
    }
}

int _Condition::wait(Mutex m,long int timeInterval) {
    pthread_mutex_t* mutex_t = m->getMutex_t();
    if(timeInterval == 0) {
        if(pthread_cond_wait(&cond_t,m->getMutex_t()) != 0) {
            Trigger(IllegalStateException,"wait failed!!");
        }
        return 0;
    }

    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    int ret = pthread_cond_timedwait(&cond_t,mutex_t,&ts);
    if(ret == ETIMEDOUT) {
        return -WaitTimeout;
    } else if(ret == 0) {
        return 0;
    }
    Trigger(IllegalStateException,"wait failed!!");
    return -1;
}

void _Condition::notify() {
    pthread_cond_signal(&cond_t);
}

void _Condition::notifyAll() {
    pthread_cond_broadcast(&cond_t);
}

_Condition::~_Condition() {
    pthread_cond_destroy(&cond_t);
}

}