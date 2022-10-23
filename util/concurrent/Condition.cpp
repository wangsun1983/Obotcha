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

#include "AutoLock.hpp"
#include "Condition.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "Mutex.hpp"
#include "System.hpp"
#include "Log.hpp"
#include "OStdInstanceOf.hpp"
#include "TimeWatcher.hpp"

namespace obotcha {

_Condition::_Condition() {
    if (pthread_cond_init(&cond_t, nullptr) != 0) {
        Trigger(InitializeException, "Condition error");
    }
}

int _Condition::wait(Mutex &m, long int interval) {
    pthread_mutex_t *mutex_t = m->getMutex_t();
    if (interval == 0) {
        return -pthread_cond_wait(&cond_t, m->getMutex_t());
    }

    struct timespec ts = {0};
    st(System)::getNextTime(interval, &ts);
    return -pthread_cond_timedwait(&cond_t, mutex_t, &ts);
}

int _Condition::wait(AutoLock &m, long int interval) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,interval);
    }
    return -1;
}

int _Condition::wait(sp<_Mutex> &m,std::function<bool()> conditionalFunc)  {
    int ret = 0;
    while(!conditionalFunc()) {
        ret = wait(m);
    }

    return ret;
}

int _Condition::wait(AutoLock &m,std::function<bool()> conditionalFunc) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,conditionalFunc);
    }
    return -1;
}

int _Condition::wait(sp<_Mutex> &m,long int millseconds,std::function<bool()> conditionalFunc) {
    TimeWatcher watch = createTimeWatcher();
    bool isWaitForEver = (millseconds == 0);

    while(!conditionalFunc()) {
        if(isWaitForEver) {
            watch->start();
        }
        
        if(wait(m,millseconds) != 0) {
            return -ETIMEDOUT;
        }

        if(!isWaitForEver) {
            millseconds -= watch->stop();
            
            if(millseconds < 0) {
                return -ETIMEDOUT;
            }
        }
    }

    return 0;
}

int _Condition::wait(AutoLock &m,long int millseconds,std::function<bool()> conditionalFunc) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,millseconds,conditionalFunc);
    }
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

} // namespace obotcha
