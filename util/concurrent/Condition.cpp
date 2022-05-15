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
#include "IllegalStateException.hpp"
#include "InitializeException.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Log.hpp"
#include "OStdInstanceOf.hpp"
#include <condition_variable>

namespace obotcha {

_Condition::_Condition() {
    if (pthread_cond_init(&cond_t, nullptr) != 0) {
        Trigger(InitializeException, "Condition error");
    }
}

int _Condition::wait(Mutex m, long int timeInterval) {
    pthread_mutex_t *mutex_t = m->getMutex_t();
    if (timeInterval == 0) {
        return -pthread_cond_wait(&cond_t, m->getMutex_t());
    }

    struct timespec ts = {0};
    st(System)::getNextTime(timeInterval, &ts);
    return -pthread_cond_timedwait(&cond_t, mutex_t, &ts);
}

int _Condition::wait(AutoLock &m, long int millseconds) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,millseconds);
    }

    return -1;
}

int _Condition::wait(sp<_Mutex> m,std::function<bool()> p)  {
    int ret = 0;
    while(!p()) {
        ret = wait(m);
    }

    return ret;
}

int _Condition::wait(AutoLock & m,std::function<bool()> p) {
    return wait(m.mLock,p);
}

int _Condition::wait(sp<_Mutex> m,long int millseconds,std::function<bool()> p) {
    while(!p()) {
        if(wait(m,millseconds) != 0) {
            return -ETIMEDOUT;
        }
    }

    return 0;
}

int _Condition::wait(AutoLock & m,long int millseconds,std::function<bool()> p) {
    return wait(m.mLock,millseconds,p);
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
